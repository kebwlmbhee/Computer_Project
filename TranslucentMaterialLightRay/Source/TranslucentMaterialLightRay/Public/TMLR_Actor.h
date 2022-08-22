// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMLR_Actor.generated.h"

UCLASS()
class TRANSLUCENTMATERIALLIGHTRAY_API ATMLR_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMLR_Actor();

	// Add AActor from level to Array
	UPROPERTY(EditAnywhere, Category = "GenerateSceneCaptureMaterial")
	TArray<AActor*> GenerateSceneCaptureMaterial;

	// Return TArray
	TArray<AActor*> ReturnTMLR_ActorArray();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
