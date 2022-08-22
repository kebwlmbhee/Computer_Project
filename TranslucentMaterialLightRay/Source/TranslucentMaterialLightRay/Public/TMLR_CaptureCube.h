// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTargetCube.h"
#include "Components/SceneComponent.h"
#include "Components/SceneCaptureComponentCube.h"
#include "TMLR_CaptureCube.generated.h"

UCLASS()
class TRANSLUCENTMATERIALLIGHTRAY_API ATMLR_CaptureCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATMLR_CaptureCube();
	void SetRenderTargetCubeInfo(UTextureRenderTargetCube*);
	void SetHiddenActors(AActor*);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TMLR_CaptureCube")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TMLR_CaptureCube")
	USceneCaptureComponentCube* CaptureComponentCube;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
};
