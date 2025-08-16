// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioSubsystem.generated.h"

class USoundBase;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEJAMLAGS_API UAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> m_dummySound;

};
