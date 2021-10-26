// Fill out your copyright notice in the Description page of Project Settings.


#include "KS_startPawn.h"
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
AKS_startPawn::AKS_startPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	skeletaMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletaMesh"));
	RootComponent = skeletaMesh;

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(skeletaMesh);
	cameraRoot->SetRelativeLocation(FVector(5.f, -35.f, 105.f));

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AKS_startPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKS_startPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKS_startPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

