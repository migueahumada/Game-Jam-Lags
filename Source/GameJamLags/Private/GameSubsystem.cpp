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

	//LevelWidgets
	for (auto& widgetPair : m_widgetsMap)
	{
		if (!widgetPair.Key) continue;

		UUserWidget* widgetInstance = CreateWidget<UUserWidget>(playerController,widgetPair.Key);

		if (!widgetInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldn't create this widget"));
			continue;
		}

		widgetInstance->SetVisibility(ESlateVisibility::Hidden);
		widgetInstance->AddToViewport();

		widgetPair.Value = widgetInstance;
	}
}

void UGameSubsystem::ShowWidget(TSubclassOf<UUserWidget> widgetClass)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController)
	{
		return;
	}
	
	UUserWidget** widgetPtr = m_widgetsMap.Find(widgetClass);
	
	if (!widgetPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowWidget: Widget instance for class is null"));
		return;
	}
	(*widgetPtr)->SetVisibility(ESlateVisibility::Visible);
	
}

void UGameSubsystem::HideWidget(TSubclassOf<UUserWidget> widgetClass)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController)
	{
		return;
	}

	UUserWidget** widgetPtr = m_widgetsMap.Find(widgetClass);

	if (!widgetPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowWidget: Widget instance for class is null"));
		return;
	}

	(*widgetPtr)->SetVisibility(ESlateVisibility::Hidden);
	
}
