// Copyright:       Copyright (C) 2022 kebwlmbhee

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/SceneCaptureCube.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTranslucentMaterialLightRayModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked();

private:
	void RegisterMenus();

	void CheckTMLRArray(TArray<FEncapsule>);
	void TraverseTargetActorAttached();
	void GenerateSceneCaptureCube();
	void GenerateMaterial();
	void ReplaceTargetActorStaticMesh();
	void DeleteExistSceneCaptureCube(TArray<FEncapsule>);
	void ErrorText(FText);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// Spawn ATMLR_Actor
	ATMLR_Actor* Actor;

	// Check if ATMLR in level or not, TargetTagActor at least one AActor
	TArray<AActor*> TargetTagActor;

	// Traverse TMLR_Actor array
	AActor* TargetActor;

	// Get Material in the plugin Content folder
	UPROPERTY(VisibleAnywhere, Category = "Materials")
	UMaterial* M_Translucent;
	// Spawn Material Instance
	UPROPERTY(VisibleAnywhere, Category = "Materials")
	UMaterialInstanceConstant* MI_Translucent;

	// Spawn RenderTargetCube
	UTextureRenderTargetCube* RenderTargetCube;

	// Get current Resolution
	UPROPERTY(VisibleAnywhere, Category = "Materials")
	int32 CurrentActorResolution;

	// Find current level
	UWorld* World;

	bool IsContinue;

	FText DialogText;

	// Array.Num() and assign array number
	int32 TwoDimensionalArrayNum;

public:
	// Spawn SceneCaptureCube
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Capture")
	ASceneCaptureCube* CaptureCube;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Capture")
	USceneCaptureComponentCube* CaptureComponentCube;
};