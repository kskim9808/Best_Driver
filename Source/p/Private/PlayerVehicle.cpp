// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVehicle.h"
#include <Camera/CameraComponent.h>
#include "PlayerMove.h"
#include <Components/SceneComponent.h>


APlayerVehicle::APlayerVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(GetMesh());
	cameraRoot->SetRelativeLocation(FVector(5.f, -35.f, 105.f));

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);

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
