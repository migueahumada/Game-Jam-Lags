// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioSubsystem.generated.h"

class USoundBase;

// Types of Sound Surface that will be mapped 
// to different PhysicalSurfaces

UENUM(BlueprintType)
enum class ESoundSurfaces : uint8 {
	ESS_Default UMETA(DisplayName = "Default"),
	ESS_Concrete UMETA(DisplayName = "Concrete"),
	ESS_Wood UMETA(DisplayName = "Wood"),
	ESS_Grass UMETA(DisplayName = "Grass"),
	ESS_Dirt UMETA(DisplayName = "Dirt")
};

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEJAMLAGS_API UAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//Actor used for testing purposes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> m_dummySound;

	//This actor could be used to post events using Wwise or FMOD
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> m_dummyActor;
};
