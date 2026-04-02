// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BasePawnMoveComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GAMEJAMLAGS_API UBasePawnMoveComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	virtual auto TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) -> void override;
	
};
