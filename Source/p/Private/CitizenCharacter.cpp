// Fill out your copyright notice in the Description page of Project Settings.


#include "CitizenCharacter.h"

// Sets default values
ACitizenCharacter::ACitizenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

