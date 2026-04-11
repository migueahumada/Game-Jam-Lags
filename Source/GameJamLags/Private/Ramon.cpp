// Fill out your copyright notice in the Description page of Project Settings.


#include "Ramon.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARamon::ARamon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 600.0f; 
	springArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName); 
	camera->bUsePawnControlRotation = false; 
	
	GetCharacterMovement()->GravityScale = gravityClimb;
	
}

// Called when the game starts or when spawned
void ARamon::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(mappingContext,0);
		}
	}
	
	
}

void ARamon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto* Move = GetCharacterMovement();
	
	FVector lastInput = GetLastMovementInputVector();
	
	Move->Velocity += lastInput;
	
	// Gravity shaping
	if (Move->Velocity.Z > 0)
		Move->GravityScale = gravityClimb;
	else
		Move->GravityScale = gravityFall;

	// Jump boost
	if (holdJumpKey && Move->IsFalling() && Move->Velocity.Z > 0.0f && JumpTimer < JumpBoostTime)
	{
		Move->Velocity.Z += JumpBoostAccel * DeltaTime;
		Move->Velocity.Z = FMath::Min(Move->Velocity.Z, MaxJumpZ);

		JumpTimer += DeltaTime;
	}
}

void ARamon::AsyncPhysicsTickActor(float DeltaTime, float SimTime)
{
	Super::AsyncPhysicsTickActor(DeltaTime, SimTime);
}

void ARamon::Move(const FInputActionValue& value)
{
	FVector2D movementVector = value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);
		
		const FVector forwardDirection = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);
		
		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(forwardDirection, movementVector.Y);
		AddMovementInput(rightDirection, movementVector.X);
	}
}

void ARamon::Look(const FInputActionValue& value)
{

	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

void ARamon::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	
	D("Ramon Jumped");
	GetCharacterMovement()->MaxWalkSpeed = 1000.0F;
	GetCharacterMovement()->bNotifyApex = true;	
	
	GetCharacterMovement()->GravityScale = gravityClimb;
}

void ARamon::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	D("Ramon Landed!");
	
	
}

void ARamon::NotifyJumpApex()
{
	Super::NotifyJumpApex();
	
	D("Apex Reached");
	
	GetCharacterMovement()->GravityScale = gravityFall;
	
	
}

void ARamon::CharJump()
{
	Super::Jump();
	
	holdJumpKey = true;
	JumpTimer = 0.0f; // 🔥 critical
	Jump();
}


void ARamon::CharStopJumping()
{
	Super::StopJumping();
	
	holdJumpKey = false;
	StopJumping();

	JumpTimer = JumpBoostTime; // optional: cut jump early
	
	
}

void ARamon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* inputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (UInputAction** action = inputAction.Find("Jump"))
		{
			D("Jump Activated")
			inputComponent->BindAction(*action, ETriggerEvent::Triggered, this, &ARamon::CharJump);
			inputComponent->BindAction(*action, ETriggerEvent::Completed, this, &ARamon::CharStopJumping);
		}
		if (UInputAction** action = inputAction.Find("Move"))
		{	
			D("Move Activated")
			inputComponent->BindAction(*action, ETriggerEvent::Triggered, this, &ARamon::Move);
		}
		
		if (UInputAction** action = inputAction.Find("Look"))
		{	
			D("Look Activated")
			inputComponent->BindAction(*action, ETriggerEvent::Triggered, this, &ARamon::Look);
		}
	}
}

