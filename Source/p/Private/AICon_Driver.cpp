// Fill out your copyright notice in the Description page of Project Settings.


#include "AICon_Driver.h"
#include <GameFramework/Controller.h>
#include "RoadSpline.h"
#include <Components/SplineComponent.h>
#include "PlayerVehicle.h"
#include <Kismet/KismetMathLibrary.h>
#include <WheeledVehicleMovementComponent.h>
#include "CarVehicle.h"
#include <DrawDebugHelpers.h>
#include <Kismet/KismetSystemLibrary.h>


AAICon_Driver::AAICon_Driver()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAICon_Driver::BeginPlay()
{
	Super::BeginPlay();

	GetPawn();
	if(IsValid(controlledCar->currentPath))
	{
		SetUpSpline(controlledCar->currentPath);
	}
}

void AAICon_Driver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Gate.IsOpen())
	{
		Drive();
	}
}

void AAICon_Driver::GetPawn()
{
	controlledCar = Cast<ACarVehicle>(AController::GetPawn());
	if (IsValid(controlledCar))
	{
		StartDriving();
	}
}

void AAICon_Driver::Drive()
{
	if (IsValid(currentPath))
	{
		SplineDrive();
	}
}

float AAICon_Driver::Steering()
{
	return 0;
}

void AAICon_Driver::SplineDrive()
{
	splinePosition = GetSplinePosition();
	auto dis = (controlledCar->GetActorLocation() - splinePosition).Size();
	currentThrottleInput = UKismetMathLibrary::MapRangeClamped(dis, 250.f, 500.f, 0.f, 1.f);
	controlledCar->GetVehicleMovement()->SetThrottleInput(currentThrottleInput);
}

float AAICon_Driver::GetDistanceAlongSpline()
{
	bool pickA = (controlledCar->GetActorLocation() - currentPath->spline->GetLocationAtDistanceAlongSpline(distanceAlongCurrentSpline, ESplineCoordinateSpace::Local)).Size() >= distanceToPushLength;
	length = controlledCar->GetVelocity().Size();
	distanceAlongCurrentSpline = UKismetMathLibrary::SelectFloat(UKismetMathLibrary::FInterpTo_Constant(distanceAlongCurrentSpline, currentSplineLength, GetWorld()->DeltaTimeSeconds, controlledCar->GetVelocity().Size()), distanceAlongCurrentSpline, pickA);


	return distanceAlongCurrentSpline;
}

void AAICon_Driver::SetUpSpline(class ARoadSpline* currentPathReference)
{
	if (IsValid(currentPathReference))
	{
		currentPath = currentPathReference;
		currentSplineLength = currentPath->spline->GetSplineLength();
	}
	else
	{
		if (IsValid(currentPath))
		{
			currentSplineLength = currentPath->spline->GetSplineLength(); 
		}
	}
}

FVector AAICon_Driver::GetSplinePosition()
{
	endLoc = currentPath->spline->GetLocationAtDistanceAlongSpline(GetDistanceAlongSpline(), ESplineCoordinateSpace::World);
	UKismetSystemLibrary::DrawDebugLine(GetWorld(), controlledCar->GetActorLocation(), endLoc, FColor::Red, 0.f, 25.f);
	return endLoc;
}

void AAICon_Driver::StartDriving()
{
	Gate.Open();
}

