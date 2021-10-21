// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSpline.h"
#include <Components/SplineComponent.h>

// Sets default values
ARoadSpline::ARoadSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = spline;
}

// Called when the game starts or when spawned
void ARoadSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

