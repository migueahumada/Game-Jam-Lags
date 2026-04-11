// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UMeshComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class GAMEJAMLAGS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UCapsuleComponent* capsule;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class USkeletalMeshComponent* mesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class USpringArmComponent* springArm;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* mappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TMap<FName,UInputAction*> inputAction;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void Jump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
