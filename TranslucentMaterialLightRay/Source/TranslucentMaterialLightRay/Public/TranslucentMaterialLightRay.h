// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceConstant.h"
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

	void CheckTMLRArray(TArray<AActor*>);
	void TraverseArrayActorAttached();
	void GenerateCaptureCube();
	void GenerateMaterial();
	void ReplaceTargetActorStaticMesh();
	void ErrorText(FText);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	// Spawn ATMLR_Actor
	ATMLR_Actor* Actor;
	// Spawn SceneCaptureCube
	ATMLR_CaptureCube* CaptureCube;

	// Check if ATMLR in level or not, TargetTagActor at least one AActor
	TArray<AActor*> TargetTagActor;

	// Traverse TMLR_Actor array
	AActor* ArrayActor;

	// Get Material in the plugin Content folder
	UPROPERTY(VisibleAnyWhere, Category = "Materials")
	UMaterial* M_Translucent = nullptr;
	// Spawn Material Instance
	UPROPERTY(VisibleAnyWHere, Category = "Materials")
	UMaterialInstanceConstant* MI_Translucent = nullptr;
	// Spawn RenderTargetCube
	UTextureRenderTargetCube* RenderTargetCube;

	// Find current level
	UWorld* World = nullptr;

	bool IsContinue;

	FText DialogText;
};