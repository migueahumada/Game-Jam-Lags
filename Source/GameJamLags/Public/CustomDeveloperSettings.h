// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CustomDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "Blueprint Subsystems"))
class GAMEJAMLAGS_API UCustomDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Meta = (BlueprintBaseOnly))
	TArray<TSubclassOf<UGameInstanceSubsystem>> m_GameInstanceSubsystems;
};

UCLASS()

class GAMEJAMLAGS_API UGameInstanceSubsystemInitializer : public UGameInstanceSubsystem 
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override final;
};
