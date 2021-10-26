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
	GetVehicleMovement()->SetThrottleInput(speed);
}

void AOtherWheeledVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoadSpline::StaticClass(), actors);
	for (auto actor : actors)
	{
		path1 = Cast<ARoadSpline>(actor);
		arrPath.Add(path1);
	}
	
	GetVehicleMovement()->SetSteeringInput(GetPath());
}

float AOtherWheeledVehicle::GetPath()
{
	FVector loc = arrPath[0]->spline->FindTangentClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
	loc.Normalize();
	FVector mulLoc = loc * 500.f;
	auto rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), arrPath[0]->spline->FindLocationClosestToWorldLocation(mulLoc + GetActorLocation(), ESplineCoordinateSpace::World));

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

void AOtherWheeledVehicle::OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerVehicle>(OtherActor);
	auto me = Cast<AOtherWheeledVehicle>(OtherActor);
	if (player || me)
	{
		Stop();
	}
}

void AOtherWheeledVehicle::OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Move();
}
