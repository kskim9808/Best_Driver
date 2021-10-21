// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVehicle.h"
#include <Camera/CameraComponent.h>
#include "PlayerMove.h"


APlayerVehicle::APlayerVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(GetMesh());
	playerCamera->SetRelativeLocation(FVector(-10.f, -35.f, 105.f));

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);
}
