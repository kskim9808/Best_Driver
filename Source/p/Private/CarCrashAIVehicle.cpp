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

	// 스플라인을 가리킬수있는 회전값을 steering에 넣어줌
	GetVehicleMovement()->SetSteeringInput(GetPath());
}

float ACarCrashAIVehicle::GetPath()
{
	// 정해놓은 path(길)이 없을 경우 steering 0값 반환
	if (path1 == nullptr)
	{
		return 0;
	}
	// 정해놓은 path(길)의 월드에 배치한 spline 의 가장 가까운 접선의 벡터를 가져옴
	FVector loc = path1->spline->FindTangentClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	loc.Normalize();
	FVector mulLoc = loc * 500.f;
	// 해당 방향으로 회전할 수 있게 하는 회전값을 가져옴
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