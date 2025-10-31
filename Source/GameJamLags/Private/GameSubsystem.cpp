// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 


/*
* Crea el widget de la widget class y lo coloca en el mapa de widgets por nivel
*/
void UGameSubsystem::InitLevelWidgets(EGameLevel gameLevel)
{
	
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController)
	{
		return;
	}

	auto currentWidgetMap = m_levelWidgetMaps.Find(gameLevel)->WidgetMap;

	for (auto& widgetPair : currentWidgetMap)
	{
		if (!widgetPair.Key) continue;

		UUserWidget* widgetInstance = CreateWidget<UUserWidget>(playerController,widgetPair.Key);

		if (!widgetInstance)
		{
			UE_LOG(LogTemp, Warning,
						 TEXT("Couldn't initialize the widget instance %s."),
						 *widgetPair.Key->GetName());
			return;
		}

		widgetPair.Value = widgetInstance;
	}
}

/// <summary>
/// Crea todos lo widgets de volón pinpon, no olvides también meterlos 
/// en el BP_GameSubsystem y llamar esta madre en el GM sino ya mamó.
/// </summary>
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
			UE_LOG(	LogTemp, Warning, 
							TEXT("Couldn't initialize the widget instance %s."), 
							*widgetPair.Key->GetName());
			continue;
		}

		widgetPair.Value = widgetInstance;
	}
}

/*
	1.- Busca si existe la widgetClass en el widgetMap.
	2.- Lo añade al viewport
	3.- Cambia la vista a que se vea
	4.- Setea el input mode de UI
	5.- Muestra el cursor del mouse
*/
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

	if (!(*widgetPtr)->IsInViewport())
	{
		(*widgetPtr)->AddToViewport();
	}

	(*widgetPtr)->SetVisibility(ESlateVisibility::Visible);
	
	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus((*widgetPtr)->TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(inputMode);
	playerController->SetShowMouseCursor(true);
}

/*
	1.- Busca si existe el widgetClass en el widgetMap.
	2.- Lo añade al viewport
	3.- Cambia la vista a que se vea
	4.- Setea el input mode de Game
	5.- Deja de mostrar el cursor del mouse
*/
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

	if ((*widgetPtr)->IsInViewport())
	{
		(*widgetPtr)->RemoveFromViewport();
	}
	
	(*widgetPtr)->SetVisibility(ESlateVisibility::Hidden);
	(*widgetPtr)->RemoveFromViewport();

	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->SetShowMouseCursor(false);
	playerController->SetPause(false);
}


void UGameSubsystem::Pause()
{
	
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	//Si no hay PC, o el WidgetMap no contiene la clase, o el juego está en pausa regresa alv.
	if (!playerController 
			|| !m_widgetsMap.Contains(m_pauseWidgetClass) 
			|| m_isGamePaused)
	{
		return;
	}

	//Si la clase de widgets está en el mapa, dame un puntero del cabrón.
	UUserWidget** widgetPtr = m_widgetsMap.Find(m_pauseWidgetClass);
	if (!widgetPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find the widget on the widgetsMaps"));
		return;
	}

	//Si el widget ya no está en el viewport pues añádelo compadre
	if (!(*widgetPtr)->IsInViewport())
	{
		(*widgetPtr)->AddToViewport();
	}

	//Muéstralo y el UI también
	(*widgetPtr)->SetVisibility(ESlateVisibility::Visible);

	//Setea el tipo de input que tendrá que será el de la UI
	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus((*widgetPtr)->TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(inputMode);

	//Muestra el cursor del mouse
	playerController->SetShowMouseCursor(true);

	//Pausa esa madre cawn
	playerController->SetPause(true);
	
	m_isGamePaused = true;
}

void UGameSubsystem::Unpause()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!playerController 
			|| !m_widgetsMap.Contains(m_pauseWidgetClass)
			|| !m_isGamePaused)
	{
		return;
	}

	UUserWidget** widgetPtr = m_widgetsMap.Find(m_pauseWidgetClass);

	if (!widgetPtr) return;

	if ((*widgetPtr)->IsInViewport())
	{
		(*widgetPtr)->RemoveFromViewport();
	}

	playerController->SetShowMouseCursor(false);
	playerController->SetPause(false);
	playerController->SetInputMode(FInputModeGameOnly());
	(*widgetPtr)->SetVisibility(ESlateVisibility::Hidden);

	m_isGamePaused = false;
}
