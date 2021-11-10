// Fill out your copyright notice in the Description page of Project Settings.


#include "CarCrashAIVehicle.h"
#include <Components/BoxComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <WheeledVehicleMovementComponent.h>
#include <Components/SplineComponent.h>
#include "RoadSpline.h"

ACarCrashAIVehicle::ACarCrashAIVehicle()
{
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComp->SetupAttachment(GetMesh());
}

void ACarCrashAIVehicle::BeginPlay()
{
	Super::BeginPlay();

	Move();
}

void ACarCrashAIVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ���ö����� ����ų���ִ� ȸ������ steering�� �־���
	GetVehicleMovement()->SetSteeringInput(GetPath());
}

float ACarCrashAIVehicle::GetPath()
{
	// ���س��� path(��)�� ���� ��� steering 0�� ��ȯ
	if (path1 == nullptr)
	{
		return 0;
	}
	// ���س��� path(��)�� ���忡 ��ġ�� spline �� ���� ����� ������ ���͸� ������
	FVector loc = path1->spline->FindTangentClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	loc.Normalize();
	FVector mulLoc = loc * 500.f;
	// �ش� �������� ȸ���� �� �ְ� �ϴ� ȸ������ ������
	auto rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), path1->spline->FindLocationClosestToWorldLocation(mulLoc + GetActorLocation(), ESplineCoordinateSpace::World));

	return UKismetMathLibrary::MapRangeClamped(UKismetMathLibrary::NormalizedDeltaRotator(rot, GetActorRotation()).Yaw, -90.f, 90.f, -1.f, 1.f);
}

void ACarCrashAIVehicle::Stop()
{
	GetVehicleMovement()->SetThrottleInput(0.0f);
	GetVehicleMovement()->SetBrakeInput(true);
}

void ACarCrashAIVehicle::Move()
{
	GetVehicleMovement()->SetThrottleInput(speed);
	GetVehicleMovement()->SetBrakeInput(false);
}