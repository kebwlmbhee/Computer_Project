// Copyright:       Copyright (C) 2022 kebwlmbhee


#include "TMLR_CaptureCube.h"

// Sets default values
ATMLR_CaptureCube::ATMLR_CaptureCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add Scene Capture Cube component to actor
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CaptureComponentCube = CreateDefaultSubobject<USceneCaptureComponentCube>(TEXT("CaptureComponentCube"));
	RootComponent = SceneComponent;
	CaptureComponentCube->SetupAttachment(SceneComponent);
	CaptureComponentCube->bCaptureEveryFrame = false;
	CaptureComponentCube->TextureTarget = nullptr;
}

// Called when the game starts or when spawned
void ATMLR_CaptureCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATMLR_CaptureCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMLR_CaptureCube::SetRenderTargetCubeInfo(UTextureRenderTargetCube* RenderCube)
{
	// Set SizeX
	RenderCube->SizeX = 256;
	RenderCube->UpdateResource();
	
	// Set TextureTarget
	CaptureComponentCube->TextureTarget = RenderCube;
	CaptureComponentCube->UpdateContent();
}

void ATMLR_CaptureCube::SetHiddenActors(AActor* HiddenActor)
{
	// Check if HiddenActor is exist or not
	if (CaptureComponentCube->HiddenActors.IsEmpty())
		CaptureComponentCube->HiddenActors.Add(HiddenActor);

	// Traverse to check if HiddenActor is exist or not
	for (auto& itor : CaptureComponentCube->HiddenActors)
	{
		if (itor.Get()->GetActorNameOrLabel() != HiddenActor->GetActorNameOrLabel())
			CaptureComponentCube->HiddenActors.Add(HiddenActor);
	}
}

