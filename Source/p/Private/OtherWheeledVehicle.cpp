// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherWheeledVehicle.h"
#include "RoadSpline.h"
#include <Components/SplineComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <WheeledVehicle.h>
#include <WheeledVehicleMovementComponent.h>
#include <Perception/PawnSensingComponent.h>
#include "PlayerVehicle.h"
#include <Components/BoxComponent.h>


AOtherWheeledVehicle::AOtherWheeledVehicle()
{
	GetMesh()->SetCollisionProfileName(TEXT("OtherCar"));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	boxComp->SetupAttachment(GetMesh());
}

void AOtherWheeledVehicle::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AOtherWheeledVehicle::OnCarBeginOverlap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AOtherWheeledVehicle::OnCarEndOverlap);

/*
	if (arrPath.Num() == 0)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoadSpline::StaticClass(), actors);
		for (auto actor : actors)
		{
			path1 = Cast<ARoadSpline>(actor);
			arrPath.Add(path1);
		}
	}*/
	Spawn();
	Move();
}

void AOtherWheeledVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetVehicleMovement()->SetSteeringInput(GetPath());
}

float AOtherWheeledVehicle::GetPath()
{
	if (path1 == nullptr)
	{
		return 0;
	}

	FVector loc = path1->spline->FindTangentClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	loc.Normalize();
	FVector mulLoc = loc * 500.f;
	auto rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), path1->spline->FindLocationClosestToWorldLocation(mulLoc + GetActorLocation(), ESplineCoordinateSpace::World));

	return UKismetMathLibrary::MapRangeClamped(UKismetMathLibrary::NormalizedDeltaRotator(rot, GetActorRotation()).Yaw, -90.f, 90.f, -1.f, 1.f);
}

void AOtherWheeledVehicle::Stop()
{
	GetVehicleMovement()->SetThrottleInput(0.0f);
	GetVehicleMovement()->SetBrakeInput(true);
}

void AOtherWheeledVehicle::Move()
{
	GetVehicleMovement()->SetThrottleInput(speed);
	GetVehicleMovement()->SetBrakeInput(false);
}
// ?????? ???????? ???? ???? ???????????????????? ???????? skeletal mesh ?? ??????
void AOtherWheeledVehicle::Spawn()
{
	if (cars.Num() == 0 || carAnimation.Num() == 0)
	{
		return;
	}
	carNum = UKismetMathLibrary::RandomIntegerInRange(0, 3);
	GetMesh()->SetSkeletalMesh(cars[carNum], true);
	GetMesh()->SetAnimInstanceClass(carAnimation[carNum]);
	Move();
}
// ???? ???????? ?????????? ???? ???????? ???????? ????
void AOtherWheeledVehicle::OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerVehicle>(OtherActor);
	auto me = Cast<AOtherWheeledVehicle>(OtherActor);
	if (player || me)
	{
		Stop();
	}
}
// ???????? ?????? ???? ??????
void AOtherWheeledVehicle::OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Move();
}
