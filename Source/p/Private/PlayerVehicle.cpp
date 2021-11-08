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

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));


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

	/*if (IsGripRight)
	{

		
	}
	else
	{
		FVector wheelLoc = steeringWheelLeft->GetComponentLocation() - wheelLeftCollision->GetComponentLocation();
	objValueLeft = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + wheelLoc.Z, -90, 90);
	steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, objValueLeft));
	}*/

	
	FVector wheelLoc = steeringWheelRight->GetComponentLocation() - wheelRightCollision->GetComponentLocation();
	objValueRight = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + wheelLoc.Z, -90, 90);
	if (IsGripRight == false)
	{
		wheelRightCollision->SetWorldLocation(steeringWheelRight->GetComponentLocation());
		objValueRight = 0.f;
	}
	steeringWheel->SetWorldRotation(FRotator(steeringWheel->GetComponentRotation().Pitch, steeringWheel->GetComponentRotation().Yaw, objValueRight));
	wheelLeftCollision->SetWorldLocation(steeringWheelLeft->GetComponentLocation());
	

}

void APlayerVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerMove->SetupPlayerInputComponent(PlayerInputComponent);
	grabRightComp->SetupPlayerInputComponent(PlayerInputComponent);
	grabLeftComp->SetupPlayerInputComponent(PlayerInputComponent);
}

