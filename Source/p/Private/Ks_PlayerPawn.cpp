// Fill out your copyright notice in the Description page of Project Settings.


#include "Ks_PlayerPawn.h"
#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>
#include "PlayerMove.h"
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>

// Sets default values
AKs_PlayerPawn::AKs_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKs_PlayerPawn::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;


	bodyMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car"));
	SetRootComponent(bodyMesh);

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(bodyMesh);
	
	/*cameraRoot->SetupAttachment(GetMesh());*/

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	


	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	

	


}

// Called every frame
void AKs_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKs_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	playerMove->SetupPlayerInputComponent(PlayerInputComponent);
}

