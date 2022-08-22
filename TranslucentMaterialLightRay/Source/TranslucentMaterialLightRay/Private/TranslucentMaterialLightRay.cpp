// Copyright Epic Games, Inc. All Rights Reserved.

#include "TranslucentMaterialLightRay.h"
#include "TranslucentMaterialLightRayStyle.h"
#include "TranslucentMaterialLightRayCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Kismet/GamePlayStatics.h"
#include "LevelEditorViewport.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/Object.h"
#include "TMLR_Actor.h"
#include "TMLR_CaptureCube.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialExpressionTextureSampleParameterCube.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Modules/ModuleManager.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "EditorAssetLibrary.h"
#include "Engine/TextureRenderTargetCube.h"

static const FName TranslucentMaterialLightRayTabName("TranslucentMaterialLightRay");

#define LOCTEXT_NAMESPACE "FTranslucentMaterialLightRayModule"

void FTranslucentMaterialLightRayModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTranslucentMaterialLightRayStyle::Initialize();
	FTranslucentMaterialLightRayStyle::ReloadTextures();

	FTranslucentMaterialLightRayCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTranslucentMaterialLightRayCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FTranslucentMaterialLightRayModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTranslucentMaterialLightRayModule::RegisterMenus));
}

void FTranslucentMaterialLightRayModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTranslucentMaterialLightRayStyle::Shutdown();

	FTranslucentMaterialLightRayCommands::Unregister();
}

void FTranslucentMaterialLightRayModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here

	// Find current level
	World = GCurrentLevelEditingViewportClient->GetWorld();

	// Make sure if continue or not
	IsContinue = true;

	if (World != nullptr)
	{
		// Traverse level AActor and find "TMLR_TAG" tag
		UGameplayStatics::GetAllActorsWithTag(World, FName(TEXT("TMLR_TAG")), TargetTagActor);

		// If tag is not detected
		if (TargetTagActor.IsEmpty())
		{
			// Spawn ATMLR_Actor
			Actor = World->SpawnActor<ATMLR_Actor>(FVector(0, 0, 0), FRotator::ZeroRotator);
			// Add Tag
			Actor->Tags.Add(FName("TMLR_TAG"));

			// Message Text
			DialogText = FText::FromString("Create TranslucentMaterialLightRay Actor!");
			FMessageDialog::Open(EAppMsgType::Ok, DialogText);

			// GEditor->RedrawLevelEditingViewports(true);		// Can not put behind else clause
		}
		// If tag is detected
		else
		{
			Actor = (ATMLR_Actor*)TargetTagActor[0];
			// Message Text
			DialogText = FText::FromString("\
TranslucentMaterialLightRay Actor is Already Exist!\n\n\
             The number of Target Actor(s): " + FString::FromInt(int32(Actor->ReturnTMLR_ActorArray().Num())) + "\n\
                            Traverse Array?\
");
			EAppReturnType::Type const Choice = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);
			{
				// Click Yes Button => Check Array
				if (Choice == EAppReturnType::Type::Yes)
				{
					CheckTMLRArray(Actor->ReturnTMLR_ActorArray());
				}
				// Click No button or close window
			}
		}
	}
}

void FTranslucentMaterialLightRayModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTranslucentMaterialLightRayCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTranslucentMaterialLightRayCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FTranslucentMaterialLightRayModule::CheckTMLRArray(TArray<AActor*> TargetArray)
{
	// Initialize ArrayActor
	ArrayActor = nullptr;

	// Traverse ATMLR_Actor array
	for (int i = 0; i < TargetArray.Num(); ++i)
	{
		ArrayActor = TargetArray[i];
		if (ArrayActor == nullptr)
			continue;

		if (!IsContinue)
			return;

		TraverseArrayActorAttached();
		GenerateMaterial();
		ReplaceTargetActorStaticMesh();
	}

	// Final Message
	DialogText = FText::FromString("Everything is Already Done!");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FTranslucentMaterialLightRayModule::TraverseArrayActorAttached()
{
	if (!IsContinue)
		return;

	// Traverse ArrayActor AttachActor to find ATMLR_CaptureCube
	TArray<AActor*> AttachedActors;
	ArrayActor->GetAttachedActors(AttachedActors);

	if (AttachedActors.IsEmpty())
	{
		GenerateCaptureCube();
	}

	for (int i = 0; i < AttachedActors.Num(); ++i)
	{
		// If find ATMLR_CaptureCube
		if (AttachedActors[i]->GetClass()->GetName() == "TMLR_CaptureCube")
		{
			CaptureCube = (ATMLR_CaptureCube*)AttachedActors[i];
			break;
		}
		// if not find ATMLR_CaptureCube
		else if (i == AttachedActors.Num() - 1)
		{
			GenerateCaptureCube();
		}
	}
}

void FTranslucentMaterialLightRayModule::GenerateCaptureCube()
{
	// Spawn CaptureCube
	CaptureCube = World->SpawnActor<ATMLR_CaptureCube>(FVector(0, 0, 0), FRotator::ZeroRotator);
	// SetParent
	CaptureCube->AttachToActor(ArrayActor, FAttachmentTransformRules::KeepRelativeTransform);
}


void FTranslucentMaterialLightRayModule::GenerateMaterial()
{
	if (!IsContinue)
		return;

	// Load Material
	FString Path = "Material'/TranslucentMaterialLightRay/M_Translucent.M_Translucent'";
	M_Translucent = LoadObject<UMaterial>(nullptr, *Path);

	// Error Message
	if (!M_Translucent)
	{
		DialogText = FText::FromString("\
                  Can not Find M_Translucent!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
		ErrorText(DialogText);
	}

	// Try to find Render Target Cube in Content Browser
	FString PackageName = "/Game/TMLR/TMLR_TC/";
	FString MaterialBaseName = "RenderTargetCube_";
	FString Name = MaterialBaseName += ArrayActor->GetActorNameOrLabel();
	FString PackagePath = PackageName + Name;

	RenderTargetCube = nullptr;
	// If find
	if (UEditorAssetLibrary::DoesAssetExist(PackagePath))
	{
		// Loading asset
		RenderTargetCube = LoadObject<UTextureRenderTargetCube>(nullptr, *(PackageName + Name));
	}
	// If not find 
	else
	{
		// Create Package
		UPackage* Package = CreatePackage(nullptr, *PackagePath);

		// Spawn Texture Render Target Cube
		RenderTargetCube = NewObject<UTextureRenderTargetCube>(Package,
			UTextureRenderTargetCube::StaticClass(),
			*Name,
			EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);
		
		// Save asset
		FAssetRegistryModule::AssetCreated(RenderTargetCube);
		RenderTargetCube->MarkPackageDirty();
		RenderTargetCube->PostEditChange();
	}
	CaptureCube->SetRenderTargetCubeInfo(RenderTargetCube);
	CaptureCube->SetHiddenActors(ArrayActor);

	// Error Message
	if (!RenderTargetCube)
	{
		DialogText = FText::FromString("\
             Can not Spawn RenderTargetCube!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
		ErrorText(DialogText);
	}

	// =========================================================== //

	// Create Factory
	UMaterialInstanceConstantFactoryNew* Factory =
		NewObject<UMaterialInstanceConstantFactoryNew>();
	Factory->InitialParent = M_Translucent;

	// Try to find Material Instance in Content Browser
	PackageName = "/Game/TMLR/TMLR_Mesh/";
	MaterialBaseName = "MI_Translucent_";
	Name = MaterialBaseName += ArrayActor->GetActorNameOrLabel();
	PackagePath = PackageName + Name;

	MI_Translucent = nullptr;
	// If find
	if (UEditorAssetLibrary::DoesAssetExist(PackagePath))
	{
		// Load asset
		MI_Translucent = LoadObject<UMaterialInstanceConstant>(nullptr, *(PackagePath));
	}
	// If not found
	else
	{
		// Load necessary modules
		FAssetToolsModule& AssetToolsModule =
			FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");

		// Spawn Material Instance
		MI_Translucent = CastChecked<UMaterialInstanceConstant>(
			AssetToolsModule.Get().CreateAsset(Name,
				FPackageName::GetLongPackagePath(PackageName),
				UMaterialInstanceConstant::StaticClass(),
				Factory)
			);
	}

	// Error Message
	if (!MI_Translucent)
	{
		DialogText = FText::FromString("\
               Can not Spawn MI_Translucent!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
	ErrorText(DialogText);
	}

	// Set Material Instance parameter
	MI_Translucent->SetTextureParameterValueEditorOnly(FName("Reflection_Param"), RenderTargetCube);
	MI_Translucent->SetTextureParameterValueEditorOnly(FName("Refraction_Param"), RenderTargetCube);

	// Save Material Instance asset
	MI_Translucent->SetFlags(RF_Standalone);
	MI_Translucent->MarkPackageDirty();
	MI_Translucent->PostEditChange();

}

void FTranslucentMaterialLightRayModule::ReplaceTargetActorStaticMesh()
{
	if (!IsContinue)
		return;

	// Traverse TargetActor to find StaticMeshComponent and replace Material
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	// Find target actor components
	TArray<UStaticMeshComponent*> Components;
	ArrayActor->GetComponents(Components);

	for (int32 i = 0; i < Components.Num(); ++i)
	{
		// Find target actor StaticMeshComponent
		StaticMeshComponent = Components[i];
		if (StaticMeshComponent != nullptr)
		{
			StaticMeshComponent->SetMaterial(0, MI_Translucent);
			StaticMeshComponent = nullptr;
			break;
		}
		else if (i == Components.Num() - 1)
		{
			DialogText = FText::FromString("\
Can not find StaticMeshComponents of " + ArrayActor->GetActorNameOrLabel() + ".\n\n\
         Skip this actor and continue execution?\
");
			EAppReturnType::Type const Choice = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);
			{
				// Click Yes Button => continue execution
				if (Choice == EAppReturnType::Type::Yes);
				// Click No button or close window => break execution
				else
				{
					IsContinue = false;
				}
			}
		}
	}
}

void FTranslucentMaterialLightRayModule::ErrorText(FText DialogMessage)
{
	FMessageDialog::Open(EAppMsgType::Ok, DialogMessage);
	IsContinue = false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTranslucentMaterialLightRayModule, TranslucentMaterialLightRay)
