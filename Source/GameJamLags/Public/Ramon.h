// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ramon.generated.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class FTimeline;

UCLASS()
class GAMEJAMLAGS_API ARamon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARamon();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USpringArmComponent* springArm;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* camera;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UInputMappingContext* mappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TMap<FName,UInputAction*> inputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float gravityClimb = 2.57f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float gravityFall = 3.51f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float JumpBoostTime = 0.0312f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float JumpBoostAccel = 9251.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MaxJumpZ = 16528.0f;

	float JumpTimer = 0.0f;

	bool holdJumpKey = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UTimelineComponent* jumpTimeline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void Move(const FInputActionValue& value);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void Look(const FInputActionValue& value);
	
	virtual void OnJumped_Implementation() override;
	
	virtual void Landed(const FHitResult& Hit) override;
	
	virtual void NotifyJumpApex() override;
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void CharJump();
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void CharStopJumping();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void AsyncPhysicsTickActor(float DeltaTime, float SimTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
