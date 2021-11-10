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

	// ī�޶� ������
	GetMesh()->SetCollisionProfileName(TEXT("Player"));
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	cameraRoot->SetupAttachment(GetMesh());
	cameraRoot->SetRelativeLocation(FVector(5.f, -35.f, 105.f));
	// ī�޶�
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	playerCamera->SetupAttachment(cameraRoot);
	// vr �޼� ��� ��Ʈ�ѷ�
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";
	// vr ������ ��� ��Ʈ�ѷ�
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";
	// �޼� ���̷�Ż �޽�
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));
	leftHand->SetRelativeLocation(FVector(-10.f, 0, 0));
	// ������ ���̷�Ż �޽�
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));
	rightHand->SetRelativeLocation(FVector(-10.f, 0, 0));
	// �ڵ��� �� ������
	steeringWheelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SteeringWheelRoot"));
	steeringWheelRoot->SetupAttachment(GetMesh());
	steeringWheelRoot->SetRelativeLocation(FVector(48.f, -37.f, 80.f));
	steeringWheelRoot->SetRelativeRotation(FRotator(-10.f, 0, 0));
	// �ڵ��� �� �޽�
	steeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	steeringWheel->SetupAttachment(steeringWheelRoot);
	// �޼� �������� ���� �ڵ��� ���� ����
	steeringWheelLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelLeft"));
	steeringWheelLeft->SetupAttachment(steeringWheel);
	steeringWheelLeft->SetRelativeLocation(FVector(0, -17.f, 0));
	steeringWheelLeft->SetRelativeRotation(FRotator(90.f,0,0));
	// �޼� �������� ���� �ڵ��� ���� ����
	steeringWheelRight = CreateDefaultSubobject<UArrowComponent>(TEXT("SteeringWheelRight"));
	steeringWheelRight->SetupAttachment(steeringWheel);
	steeringWheelRight->SetRelativeLocation(FVector(0, 17.f, 0));
	steeringWheelRight->SetRelativeRotation(FRotator(-90.f, 0, 0));
	// �޼� Grip �� �ڵ��� �� ��� �ִ� �޽�
	leftVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftVisibleHand"));
	leftVisibleHand->SetupAttachment(steeringWheel);
	leftVisibleHand->SetVisibility(false);
	// ������ Grip �� �ڵ��� �� ��� �ִ� �޽�
	rightVisibleHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightVisibleHand"));
	rightVisibleHand->SetupAttachment(steeringWheel);
	rightVisibleHand->SetVisibility(false);
	// �޼����� ��� �ڵ鸵 �� �浹ü
	wheelLeftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelLeftCollision"));
	wheelLeftCollision->SetupAttachment(steeringWheelRoot);
	wheelLeftCollision->SetSphereRadius(3.f);
	// �޼����� ��� �ڵ鸵 �� �浹ü
	wheelRightCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SteeringWheelRightCollision"));
	wheelRightCollision->SetupAttachment(steeringWheelRoot);
	wheelRightCollision->SetSphereRadius(3.f);

	// �ſ��� ������(�ݻ����)
	mirrorRoot = CreateDefaultSubobject<UPlanarReflectionComponent>(TEXT("MirrorRoot"));
	mirrorRoot->SetupAttachment(GetMesh());
	mirrorRoot->SetRelativeLocation(FVector(50.f, 0, 90.f));
	mirrorRoot->SetRelativeRotation(FRotator(90.f, 0, 0));
	mirrorRoot->SetRelativeScale3D(FVector(0.1f, 0.1f, 1.f));
	mirrorRoot->DistanceFromPlaneFadeoutStart = 1500.f;
	mirrorRoot->ScreenPercentage = 100.f;
	// ���� ���̵�̷�
	leftSideMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftSideMirror"));
	leftSideMirror->SetupAttachment(mirrorRoot);
	leftSideMirror->SetRelativeLocation(FVector(54.f, -798.f, 0));
	leftSideMirror->SetRelativeRotation(FRotator(0, 4.4f, 0));
	leftSideMirror->SetRelativeScale3D(FVector(0.87f, 1.7f, 1.f));
	leftSideMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// ������ ���̵�̷�
	rightSideMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightSideMirror"));
	rightSideMirror->SetupAttachment(mirrorRoot);
	rightSideMirror->SetRelativeLocation(FVector(54.f, 807.f, 0));
	rightSideMirror->SetRelativeRotation(FRotator(0, -4.4f, 0));
	rightSideMirror->SetRelativeScale3D(FVector(0.87f, 1.7f, 1.f));
	rightSideMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// �Ĺ� �̷�
	backMirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackMirror"));
	backMirror->SetupAttachment(mirrorRoot);
	backMirror->SetRelativeLocation(FVector(212.f, 8.f, 26.8f));
	backMirror->SetRelativeRotation(FRotator(10.f, 0, 0));
	backMirror->SetRelativeScale3D(FVector(0.57f, 1.55f, 1.f));
	backMirror->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// �����ϸ鼭 ��� UI ���� ������Ʈ
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

	// �ڵ��� �� ��ġ
	// ���������� ������ ���� ����
	FVector wheelRightLoc = steeringWheelRight->GetComponentLocation() - wheelRightCollision->GetComponentLocation();
	objValueRight = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + wheelRightLoc.Z, -90, 90);
	// �޼����� ������ ���� ����
	FVector wheelLeftLoc = steeringWheelLeft->GetComponentLocation() - wheelLeftCollision->GetComponentLocation();
	objValueLeft = UKismetMathLibrary::Clamp(steeringWheel->GetComponentRotation().Roll + -wheelLeftLoc.Z, -90, 90);

	// ������� Grip �� �ڵ��� ������ ������ �������� �����̰� �ϰ�
	// �޼����� Grip �� �޼ձ��� ���������� Grip �� ������ ����
	// ��� �ƴ� �� ���� ��ġ�� ���ƿ���
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

