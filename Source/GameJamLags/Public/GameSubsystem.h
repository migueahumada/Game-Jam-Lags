// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSubsystem.generated.h"

class UUserWidget;
class UWorld;

UENUM(BlueprintType)
enum class EGameLevel : uint8
{
	EGL_Menu				UMETA(DisplayName = "Menu Level"),
	EGL_Park				UMETA(DisplayName = "Park Level"),
	EGL_Tianguis		UMETA(DisplayName = "Tianguis Level"),
	EGL_Parisina		UMETA(DisplayName = "Parisina Level"),
	EGL_Techos			UMETA(DisplayName = "Techos Level"),
	EGL_Trajineras	UMETA(DisplayName = "Trajineras Level"),
	EGL_Feria				UMETA(DisplayName = "Feria Level"),
	EGL_Fin					UMETA(DisplayName = "Fin Level")
};

//Estructura que tendrá un mapa de la clase que cargaremos
//junto con el objeto que crearemos del widget.
USTRUCT(BlueprintType)
struct FLevelWidgetMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "WidgetMap")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> WidgetMap;
};

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEJAMLAGS_API UGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	/*
		Mapa de LevelWidgets que contiene los widgets que se necesitarán
		cargar en memoria al comienzo del nivel.
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TMap<EGameLevel, FLevelWidgetMap> m_levelWidgetMaps;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> m_pauseWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TMap<TSubclassOf<UUserWidget>, UUserWidget*> m_widgetsMap;

	UPROPERTY(VisibleAnywhere, Category = "Widgets")
	bool m_isGamePaused = false;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void InitLevelWidgets(EGameLevel gameLevel);

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
