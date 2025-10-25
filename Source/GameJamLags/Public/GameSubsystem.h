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
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> m_pauseWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> m_widgetsMap;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	bool m_isGamePaused = false;

public:
	UFUNCTION(BlueprintCallable)
	void InitWidgets();

	UFUNCTION(BlueprintCallable)
	void ShowWidget(TSubclassOf<UUserWidget> widgetClass);

	UFUNCTION(BlueprintCallable)
	void HideWidget(TSubclassOf<UUserWidget> widgetClass);

	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Unpause();

	UFUNCTION(BlueprintCallable)
	const bool IsGamePaused() const
	{
		return m_isGamePaused;
	}


};
