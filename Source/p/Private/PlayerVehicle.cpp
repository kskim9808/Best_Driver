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
#include <Components/PlanarReflectionComponent.h>


APlayerVehicle::APlayerVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 기준점
	GetMesh()->SetCollisionProfileName(TEXT("Player"));
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(GetMesh());
	cameraRoot->SetRelativeLocation(FVector(5.f, -35.f, 105.f));
	// 카메라
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);
	// vr 왼손 모션 컨트롤러
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";
	// vr 오른손 모션 컨트롤러
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";
	// 왼손 스켈레탈 메쉬
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));
	leftHand->SetRelativeLocation(FVector(-10.f, 0, 0));
	// 오른손 스켈레탈 메쉬
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));
	rightHand->SetRelativeLocation(FVector(-10.f, 0, 0));
	// 자동차 휠 기준점
	steeringWheelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SteeringWheelRoot"));
	steeringWheelRoot->SetupAttachment(GetMesh());
	steeringWheelRoot->SetRelativeLocation(FVector(48.f, -37.f, 80.f));
	steeringWheelRoot->SetRelativeRotation(FRotator(-10.f, 0, 0));
	// 자동차 휠 메쉬
	steeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	steeringWheel->SetupAttachment(steeringWheelRoot);
	// 왼손 기준으로 돌릴 자동차 휠의 방향
	steeringWheelLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelLeft"));
	steeringWheelLeft->SetupAttachment(steeringWheel);
	steeringWheelLeft->SetRelativeLocation(FVector(0, -17.f, 0));
	steeringWheelLeft->SetRelativeRotation(FRotator(90.f,0,0));
	// 왼손 기준으로 돌릴 자동차 휠의 방향
	steeringWheelRight = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelRight"));
	steeringWheelRight->SetupAttachment(steeringWheel);
	steeringWheelRight->SetRelativeLocation(FVector(0, 17.f, 0));
	steeringWheelRight->SetRelativeRotation(FRotator(-90.f, 0, 0));
	// 왼손 Grip 시 자동차 휠 쥐고 있는 메쉬
	leftVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftVisibleHand"));
	leftVisibleHand->SetupAttachment(steeringWheel);
	leftVisibleHand->SetVisibility(false);
	// 오른손 Grip 시 자동차 휠 쥐고 있는 메쉬
	rightVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightVisibleHand"));
	rightVisibleHand->SetupAttachment(steeringWheel);
	rightVisibleHand->SetVisibility(false);
	// 왼손으로 쥐고 핸들링 할 충돌체
	wheelLeftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelLeftCollision"));
	wheelLeftCollision->SetupAttachment(steeringWheelRoot);
	wheelLeftCollision->SetSphereRadius(3.f);
	// 왼손으로 쥐고 핸들링 할 충돌체
	wheelRightCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelRightCollision"));
	wheelRightCollision->SetupAttachment(steeringWheelRoot);
	wheelRightCollision->SetSphereRadius(3.f);

	// 거울의 기준점(반사평면)
	mirrorRoot = CreateDefaultSubobject<UPlanarReflectionComponent>(TEXT("MirrorRoot"));
	mirrorRoot->SetupAttachment(GetMesh());
	mirrorRoot->SetRelativeLocation(FVector(50.f, 0, 90.f));
	mirrorRoot->SetRelativeRotation(FRotator(90.f, 0, 0));
	mirrorRoot->SetRelativeScale3D(FVector(0.1f, 0.1f, 1.f));
	mirrorRoot->DistanceFromPlaneFadeoutStart = 1500.f;
	mirrorRoot->ScreenPercentage = 100.f;
	// 왼쪽 사이드미러
	leftSideMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftSideMirror"));
	leftSideMirror->SetupAttachment(mirrorRoot);
	leftSideMirror->SetRelativeLocation(FVector(54.f, -798.f, 0));
	leftSideMirror->SetRelativeRotation(FRotator(0, 4.4f, 0));
	leftSideMirror->SetRelativeScale3D(FVector(0.87f, 1.7f, 1.f));
	leftSideMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 오른쪽 사이드미러
	rightSideMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightSideMirror"));
	rightSideMirror->SetupAttachment(mirrorRoot);
	rightSideMirror->SetRelativeLocation(FVector(54.f, 807.f, 0));
	rightSideMirror->SetRelativeRotation(FRotator(0, -4.4f, 0));
	rightSideMirror->SetRelativeScale3D(FVector(0.87f, 1.7f, 1.f));
	rightSideMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 후방 미러
	backMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMirror"));
	backMirror->SetupAttachment(mirrorRoot);
	backMirror->SetRelativeLocation(FVector(212.f, 8.f, 26.8f));
	backMirror->SetRelativeRotation(FRotator(10.f, 0, 0));
	backMirror->SetRelativeScale3D(FVector(0.57f, 1.55f, 1.f));
	backMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 진행하면서 띄울 UI 위젯 컴포넌트
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

	// 자동차 휠 위치
	// 오른손으로 움직인 휠의 정도
	FVector wheelRightLoc = steeringWheelRight->GetComponentLocation() - wheelRightCollision->GetComponentLocation();
	objValueRight = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + wheelRightLoc.Z, -90, 90);
	// 왼손으로 움직인 휠의 정도
	FVector wheelLeftLoc = steeringWheelLeft->GetComponentLocation() - wheelLeftCollision->GetComponentLocation();
	objValueLeft = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + -wheelLeftLoc.Z, -90, 90);

	// 양손으로 Grip 시 핸들의 방향을 오른손 기준으로 움직이게 하고
	// 왼손으로 Grip 시 왼손기준 오른손으로 Grip 시 오른손 기준
	// 모두 아닐 시 원래 위치로 돌아오기
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

