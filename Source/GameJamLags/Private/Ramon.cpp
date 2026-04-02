// Fill out your copyright notice in the Description page of Project Settings.


#include "Ramon.h"

// Sets default values
ARamon::ARamon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARamon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARamon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARamon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

