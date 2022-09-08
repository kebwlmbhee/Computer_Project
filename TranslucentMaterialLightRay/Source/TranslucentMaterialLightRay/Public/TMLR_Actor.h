// Copyright:       Copyright (C) 2022 kebwlmbhee

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMLR_Actor.generated.h"


USTRUCT(BlueprintType)
struct FEncapsule
{
	GENERATED_BODY()

	FEncapsule()
	{
		Resolution = TEXT("256");
	}

	// Add the actor which want to generate material instance. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEncapsule")
	TArray<AActor*> ArrayActor;
	
	// Choose render target cube resolution.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEncapsule", meta = (GetOptions = "GetResolutionOptions"))
	FName Resolution;
};

UCLASS()
class TRANSLUCENTMATERIALLIGHTRAY_API ATMLR_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMLR_Actor();

	// If true, delete the SceneCaptureCube after generate material instance.
	// You might enable this when you want to improve performance and ensure the actor position does not move.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerateMaterialInstance")
	bool DeleteSceneCaptureCube;

	UFUNCTION(CallInEditor)
	TArray<FString> GetArrayOptions() const
	{
		return { TEXT("1"), TEXT("2"), TEXT("3"), TEXT("4"), TEXT("5"), TEXT("6") };
	}

	UFUNCTION(CallInEditor)
	TArray<FString> GetResolutionOptions() const
	{
		return { TEXT("128"), TEXT("256"), TEXT("512"), TEXT("1024"), TEXT("2048"), TEXT("4096") };
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GenerateMaterialInstance")
	TArray<FEncapsule> TwoDimensionalArray;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
