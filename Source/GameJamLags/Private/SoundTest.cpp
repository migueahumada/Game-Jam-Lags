// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundTest.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
ASoundTest::ASoundTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pAudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));

	m_pAudioComponent->SetupAttachment(RootComponent);
	
	m_pAudioComponent->SetSound(m_pSound);
}

// Called when the game starts or when spawned
void ASoundTest::BeginPlay()
{
	Super::BeginPlay();
	//m_pAudioComponent->Play();
	
	
}

// Called every frame
void ASoundTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

