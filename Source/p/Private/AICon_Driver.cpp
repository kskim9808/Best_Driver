// Fill out your copyright notice in the Description page of Project Settings.


#include "AICon_Driver.h"
#include <GameFramework/Controller.h>
#include "RoadSpline.h"
#include <Components/SplineComponent.h>
#include "PlayerVehicle.h"
#include <Kismet/KismetMathLibrary.h>
#include <WheeledVehicleMovementComponent.h>
#include "CarVehicle.h"


AAICon_Driver::AAICon_Driver()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAICon_Driver::BeginPlay()
{
	Super::BeginPlay();

	GetPawn();
	if(controlledCar->currentPath)
	{
		SetUpSpline(controlledCar->currentPath);
	}
}

void AAICon_Driver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICon_Driver::GetPawn()
{
	controlledCar = Cast<ACarVehicle>(AController::GetPawn());
	if (controlledCar)
	{
		StartDriving();
	}
}

void AAICon_Driver::Drive()
{
	if (currentPath)
	{
		SplineDrive();
	}
}

void AAICon_Driver::Steering()
{

}

void AAICon_Driver::SplineDrive()
{
	auto dis = FVector::Dist(controlledCar->GetActorLocation(), GetSplinePosition());

	controlledCar->GetVehicleMovement()->SetThrottleInput(UKismetMathLibrary::MapRangeClamped(dis, 250.f, 500.f, 0.f, 1.f));

}

float AAICon_Driver::GetDistanceAlongSpline()
{
	bool pickA = FVector::Dist(controlledCar->GetActorLocation(), currentPath->spline->GetLocationAtDistanceAlongSpline(distanceAlongCurrentSpline, ESplineCoordinateSpace::Local)) >= distanceToPushLength;
	
	distanceAlongCurrentSpline = UKismetMathLibrary::SelectFloat(FMath::FInterpTo(distanceAlongCurrentSpline, setCurrentSplineLength, GetWorld()->DeltaTimeSeconds, splinePushSpeed), distanceAlongCurrentSpline, pickA);

	Loc = distanceAlongCurrentSpline;
	return distanceAlongCurrentSpline;
}

void AAICon_Driver::SetUpSpline(class ARoadSpline* currentPathReference)
{
	if (currentPathReference != nullptr)
	{
		currentPath = currentPathReference;
		setCurrentSplineLength = currentPath->spline->GetSplineLength();
		UE_LOG(LogTemp, Warning, TEXT("Good5"));

	}
}

FVector AAICon_Driver::GetSplinePosition()
{
	UE_LOG(LogTemp, Warning, TEXT("Good6"));

	return currentPath->spline->GetLocationAtDistanceAlongSpline(GetDistanceAlongSpline(), ESplineCoordinateSpace::World);
}

