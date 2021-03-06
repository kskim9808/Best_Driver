// Fill out your copyright notice in the Description page of Project Settings.


#include "CitizenCharacter.h"
#include "CitizenFSM.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
ACitizenCharacter::ACitizenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Citizen"));
	GetCharacterMovement()->MaxWalkSpeed = 700;

	citizenFSM = CreateDefaultSubobject<UCitizenFSM>(TEXT("CitizenFSM"));
}

// Called when the game starts or when spawned
void ACitizenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACitizenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACitizenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

