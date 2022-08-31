// Copyright:       Copyright (C) 2022 kebwlmbhee


#include "TMLR_Actor.h"
#include "LevelEditorViewport.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ATMLR_Actor::ATMLR_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATMLR_Actor::BeginPlay()
{
	// Super::BeginPlay();
	
}

// Called every frame
void ATMLR_Actor::Tick(float DeltaTime)
{
	// Super::Tick(DeltaTime);

}

TArray<AActor*> ATMLR_Actor::ReturnTMLR_ActorArray()
{
	return GenerateSceneCaptureMaterial;
}
