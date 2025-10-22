// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 




void UGameSubsystem::InitWidgets()
{
	
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

	if (!playerController)
	{
		return;
	}

	//Mostly used Widgets

	m_pauseWidget = CreateWidget<UUserWidget>(playerController, m_pauseWidgetClass);

	//LevelWidgets
	for (auto& widgetClass : m_widgetClasses)
	{
		if (!widgetClass)
		{
			continue;
		}

		UUserWidget* widgetPtr = CreateWidget<UUserWidget>(playerController,widgetClass);

		if (!widgetPtr)
		{
			continue;
		}
		widgetPtr->SetVisibility(ESlateVisibility::Hidden);
		widgetPtr->AddToViewport();

		m_activeWidgets.Add(widgetPtr);
	}
}

void UGameSubsystem::ShowWidget(TSubclassOf<UUserWidget> widgetClass)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController)
	{
		return;
	}

	for (auto& currentWidget : m_activeWidgets)
	{
		if (currentWidget && currentWidget->IsA(widgetClass))
		{
			//playerController->SetInputMode(FInputModeUIOnly());
			currentWidget->SetVisibility(ESlateVisibility::Visible);
			//playerController->bShowMouseCursor = true;
			break;
		}
	}
}

void UGameSubsystem::HideWidget(TSubclassOf<UUserWidget> widgetClass)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController)
	{
		return;
	}

	for (auto& currentWidget : m_activeWidgets)
	{
		if (currentWidget && currentWidget->IsA(widgetClass))
		{
			//playerController->SetInputMode(FInputModeGameOnly());
			currentWidget->SetVisibility(ESlateVisibility::Hidden);
			//playerController->bShowMouseCursor = false;
			break;
		}
	}
}
