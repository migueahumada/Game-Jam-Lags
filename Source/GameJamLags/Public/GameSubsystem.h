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
	TArray<UUserWidget*> m_activeWidgets;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TArray<TSubclassOf<UUserWidget>> m_widgetClasses;

	//Pause Widgets
	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> m_pauseWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UUserWidget* m_pauseWidget;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	UUserWidget* m_menuWidget;

public:
	
	

	UFUNCTION(BlueprintCallable)
	void InitWidgets();

	UFUNCTION(BlueprintCallable)
	void ShowWidget(TSubclassOf<UUserWidget> widgetClass);

	UFUNCTION(BlueprintCallable)
	void HideWidget(TSubclassOf<UUserWidget> widgetClass);

};
