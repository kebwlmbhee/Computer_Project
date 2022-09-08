// Copyright:       Copyright (C) 2022 kebwlmbhee

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
			DialogText = FText::FromString("Create TMLR_Actor!");
			FMessageDialog::Open(EAppMsgType::Ok, DialogText);
			return;
		}
		// If tag is detected
		else
		{
			Actor = (ATMLR_Actor*)TargetTagActor[0];

			if (Actor->DeleteSceneCaptureCube)
			{
				DeleteExistSceneCaptureCube(Actor->TwoDimensionalArray);
				return;
			}

			TwoDimensionalArrayNum = Actor->TwoDimensionalArray.Num();
			if (!TwoDimensionalArrayNum)
			{
				DialogText = FText::FromString("The element of TwoDimensionalArray is empty!");
				ErrorText(DialogText);
				return;
			}

			// Message Text
			FString TempString;
			                      
			TempString = "          TMLR_Actor is already exist!\n\n";
			for (int i = 0; i < TwoDimensionalArrayNum; ++i)
			{
				TempString += "(RES: "
					+ Actor->TwoDimensionalArray[i].Resolution.ToString()
					+ ")The number of Target Actors : "
					+ FString::FromInt(int32(Actor->TwoDimensionalArray[i].ArrayActor.Num()))
					+ "\n";
			}
			TempString += '\n';
			TempString += "             Create material instances?";

			DialogText = FText::FromString(TempString);
			EAppReturnType::Type const Choice = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);
			{
				// Click Yes Button => Check Array
				if (Choice == EAppReturnType::Type::Yes)
				{
					CheckTMLRArray(Actor->TwoDimensionalArray);

					// Final Message
					DialogText = FText::FromString("Everything is done!");
					FMessageDialog::Open(EAppMsgType::Ok, DialogText);
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

void FTranslucentMaterialLightRayModule::CheckTMLRArray(TArray<FEncapsule> Target2DArray)
{
	// Initialize TargetActor
	TargetActor = nullptr;
	
	// Traverse TwoDimensionalArray
	for (int i = 0; i < TwoDimensionalArrayNum; ++i)
	{
		// Get USTRUCT FEncapsule
		FEncapsule TargetArray = Target2DArray[i];
		for (int j = 0; j < TargetArray.ArrayActor.Num(); ++j)
		{
			// Get TArray<AActor*> and Resolution
			TargetActor = TargetArray.ArrayActor[j];
			CurrentActorResolution = FCString::Atoi(*TargetArray.Resolution.ToString());

			if (TargetActor == nullptr)
				continue;

			if (!IsContinue)
				return;

			TraverseTargetActorAttached();
			GenerateMaterial();
			ReplaceTargetActorStaticMesh();
		}
	}
}

void FTranslucentMaterialLightRayModule::TraverseTargetActorAttached()
{
	if (!IsContinue)
		return;

	CaptureCube = nullptr;
	CaptureComponentCube = nullptr;

	// Traverse TargetActor AttachActor to find ASceneCaptureCube
	TArray<AActor*> AttachedActors;
	TargetActor->GetAttachedActors(AttachedActors);

	if (AttachedActors.IsEmpty())
	{
		GenerateSceneCaptureCube();
	}

	for (int i = 0; i < AttachedActors.Num(); ++i)
	{
		// If find SceneCaptureCube
		if (AttachedActors[i]->GetClass()->GetName() == "SceneCaptureCube")
		{
			CaptureCube = (ASceneCaptureCube*)AttachedActors[i];
			break;
		}
		// if not find SceneCaptureCube
		else if (i == AttachedActors.Num() - 1)
		{
			GenerateSceneCaptureCube();
		}
	}

	// Error Message
	if (!CaptureCube)
	{
		DialogText = FText::FromString("\
              Can not find SceneCaptureCube!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
		ErrorText(DialogText);
	}

	// Assign CaptureComponentCube
	CaptureComponentCube = nullptr;
	CaptureComponentCube = CaptureCube->GetCaptureComponentCube();

	// Error Message
	if (!CaptureComponentCube)
	{
		DialogText = FText::FromString("\
          Can not find CaptureComponentCube!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
		ErrorText(DialogText);
	}
}

void FTranslucentMaterialLightRayModule::GenerateSceneCaptureCube()
{
	// Spawn CaptureCube
	CaptureCube = World->SpawnActor<ASceneCaptureCube>(FVector(0, 0, 0), FRotator::ZeroRotator);
	// SetParent
	CaptureCube->AttachToActor(TargetActor, FAttachmentTransformRules::KeepRelativeTransform);
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
				  Can not find M_Translucent!\n\n\
Please re-install TranslucentMaterialLightRay plugin.\
");
		ErrorText(DialogText);
	}

	// Try to find Render Target Cube in Content Browser
	FString PackageName = "/Game/TMLR/TMLR_TC/";
	FString MaterialBaseName = "RenderTargetCube_";
	FString Name = MaterialBaseName += TargetActor->GetActorNameOrLabel();
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
	}

	RenderTargetCube->SizeX = CurrentActorResolution;
	// Save asset
	FAssetRegistryModule::AssetCreated(RenderTargetCube);
	RenderTargetCube->MarkPackageDirty();
	RenderTargetCube->PostEditChange();

	// Check if TargetActor is exist or not
	if(CaptureComponentCube->HiddenActors.IsEmpty())
		CaptureComponentCube->HiddenActors.Add(TargetActor);

	// Traverse to check if TargetActor is exist or not
	for (auto& itor : CaptureComponentCube->HiddenActors)
	{
		if(itor.Get()->GetActorNameOrLabel() != TargetActor->GetActorNameOrLabel())
			CaptureComponentCube->HiddenActors.Add(TargetActor);
	}

	CaptureComponentCube->TextureTarget = RenderTargetCube;

	// Error Message
	if (!RenderTargetCube)
	{
		DialogText = FText::FromString("\
			 Can not spawn RenderTargetCube!\n\n\
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
	Name = MaterialBaseName += TargetActor->GetActorNameOrLabel();
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

		// Generate Material Instance
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
		         Can not spawn MI_Translucent!\n\n\
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
	TargetActor->GetComponents(Components);

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
Can not find StaticMeshComponents of " + TargetActor->GetActorNameOrLabel() + ".\n\n\
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

void FTranslucentMaterialLightRayModule::DeleteExistSceneCaptureCube(TArray<FEncapsule> Target2DArray)
{
	// Initialize TargetActor
	TargetActor = nullptr;

	DialogText = FText::FromString("\
Scene capture will no longer support for real time.\n\
                   Do you want to continue?");
	EAppReturnType::Type const Choice = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);
	{
		// Click Yes Button => continue
		if (Choice == EAppReturnType::Type::Yes);
		// Click No button or close window
		else
			return;
	}

	// Traverse TwoDimensionalArray
	for (int i = 0; i < TwoDimensionalArrayNum; ++i)
	{
		// Get USTRUCT FEncapsule
		FEncapsule TargetArray = Target2DArray[i];
		for (int j = 0; j < TargetArray.ArrayActor.Num(); ++j)
		{
			// Get TArray<AActor*>
			TargetActor = TargetArray.ArrayActor[j];
			if (!TargetActor)
				continue;

			// Find Attached Actors
			TArray<AActor*> AttachedActors;
			TargetActor->GetAttachedActors(AttachedActors);		

			// Traverse Attached Actors
			for (int k = 0; k < AttachedActors.Num(); ++k)
			{
				// If find SceneCaptureCube
				if (AttachedActors[k]->GetClass() == ASceneCaptureCube::StaticClass())
				{
					CaptureCube = (ASceneCaptureCube*)AttachedActors[k];
					CaptureCube->Destroy();
				}
			}
		}
	}
	Actor->DeleteSceneCaptureCube = false;
	DialogText = FText::FromString("SceneCaptureCubes were successfully deleted");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}


void FTranslucentMaterialLightRayModule::ErrorText(FText DialogMessage)
{
	FMessageDialog::Open(EAppMsgType::Ok, DialogMessage);
	IsContinue = false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTranslucentMaterialLightRayModule, TranslucentMaterialLightRay)
