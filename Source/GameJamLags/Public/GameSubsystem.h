// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSubsystem.generated.h"

class UUserWidget;
class UWorld;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEJAMLAGS_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	
private:

public:
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> m_widgetsMap;

	UFUNCTION(BlueprintCallable)
	void InitWidgets();

	UFUNCTION(BlueprintCallable)
	void ShowWidget(TSubclassOf<UUserWidget> widgetClass);

	UFUNCTION(BlueprintCallable)
	void HideWidget(TSubclassOf<UUserWidget> widgetClass);

};
