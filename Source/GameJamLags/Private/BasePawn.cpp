// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    if (springArm) { SetRootComponent(springArm);}
	if (camera) { camera->SetupAttachment(springArm, USpringArmComponent::SocketName); }
	if (capsule) { capsule->SetupAttachment(RootComponent);}
	if (mesh) { mesh->SetupAttachment(capsule);}
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

