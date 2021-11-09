// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVehicle.h"
#include <Camera/CameraComponent.h>
#include "PlayerMove.h"
#include <Components/SceneComponent.h>
#include <Components/WidgetComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include "GrabRightActorComponent.h"
#include <Components/ArrowComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "GrabLeftActorComponent.h"


APlayerVehicle::APlayerVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(TEXT("Player"));
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(GetMesh());
	cameraRoot->SetRelativeLocation(FVector(5.f, -35.f, 105.f));

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));
	leftHand->SetRelativeLocation(FVector(-10.f, 0, 0));
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));
	rightHand->SetRelativeLocation(FVector(-10.f, 0, 0));


	steeringWheelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SteeringWheelRoot"));
	steeringWheelRoot->SetupAttachment(GetMesh());
	steeringWheelRoot->SetRelativeLocation(FVector(48.f, -37.f, 80.f));
	steeringWheelRoot->SetRelativeRotation(FRotator(-10.f, 0, 0));
	steeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	steeringWheel->SetupAttachment(steeringWheelRoot);
	steeringWheelLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelLeft"));
	steeringWheelLeft->SetupAttachment(steeringWheel);
	steeringWheelLeft->SetRelativeLocation(FVector(0, -17.f, 0));
	steeringWheelLeft->SetRelativeRotation(FRotator(90.f,0,0));
	steeringWheelRight = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelRight"));
	steeringWheelRight->SetupAttachment(steeringWheel);
	steeringWheelRight->SetRelativeLocation(FVector(0, 17.f, 0));
	steeringWheelRight->SetRelativeRotation(FRotator(-90.f, 0, 0));
	leftVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftVisibleHand"));
	leftVisibleHand->SetupAttachment(steeringWheel);
	leftVisibleHand->SetVisibility(false);
	rightVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightVisibleHand"));
	rightVisibleHand->SetupAttachment(steeringWheel);
	rightVisibleHand->SetVisibility(false);
	wheelLeftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelLeftCollision"));
	wheelLeftCollision->SetupAttachment(steeringWheelRoot);
	wheelLeftCollision->SetSphereRadius(3.f);
	wheelRightCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelRightCollision"));
	wheelRightCollision->SetupAttachment(steeringWheelRoot);
	wheelRightCollision->SetSphereRadius(3.f);

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	widgetComp->SetupAttachment(cameraRoot);

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
	grabRightComp = CreateDefaultSubobject<UGrabRightActorComponent>(TEXT("GrabRightComponent"));
	grabLeftComp = CreateDefaultSubobject<UGrabLeftActorComponent>(TEXT("GrabLeftComponent"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerVehicle::BeginPlay()
{
	Super::BeginPlay();

	widgetComp->SetVisibility(false);
}

void APlayerVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector wheelRightLoc = steeringWheelRight->GetComponentLocation() - wheelRightCollision->GetComponentLocation();
	objValueRight = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + wheelRightLoc.Z, -90, 90);
	FVector wheelLeftLoc = steeringWheelLeft->GetComponentLocation() - wheelLeftCollision->GetComponentLocation();
	objValueLeft = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + -wheelLeftLoc.Z, -90, 90);

	if (IsGripLeft && IsGripRight)
	{
		steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, objValueRight));
	}
	else if (IsGripRight && !(IsGripLeft))
	{
		wheelLeftCollision->SetWorldLocation(steeringWheelLeft->GetComponentLocation());
		objValueLeft = 0.f;
		steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, objValueRight));
	}
	else if (IsGripLeft && !(IsGripRight))
	{
		wheelRightCollision->SetWorldLocation(steeringWheelRight->GetComponentLocation());
		objValueRight = 0.f;
		steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, objValueLeft));
	}
	else if (!(IsGripRight) && !(IsGripLeft))
	{
		objValueLeft = 0.f;
		objValueRight = 0.f;
		wheelLeftCollision->SetWorldLocation(steeringWheelLeft->GetComponentLocation());
		wheelRightCollision->SetWorldLocation(steeringWheelRight->GetComponentLocation());
		steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, 0));
	}

	
	
	

}

void APlayerVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);
	grabRightComp->SetupPlayerInputComponent(PlayerInputComponent);
	grabLeftComp->SetupPlayerInputComponent(PlayerInputComponent);
}

