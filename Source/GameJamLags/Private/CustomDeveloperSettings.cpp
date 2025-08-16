// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomDeveloperSettings.h"

void UGameInstanceSubsystemInitializer::Initialize(FSubsystemCollectionBase& Collection)
{
  const UCustomDeveloperSettings* CustomDeveloperSettings = GetDefault<UCustomDeveloperSettings>();

	if (CustomDeveloperSettings->m_GameInstanceSubsystems.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UGameInstanceSubsystemInitializer::Initialize - Empty GameInstance Subsystem array"))

		return;
	}

	for(TSubclassOf<UGameInstanceSubsystem> Subsystem : CustomDeveloperSettings->m_GameInstanceSubsystems)
	{
		Collection.InitializeDependency(Subsystem);
	}
}
