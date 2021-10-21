// Fill out your copyright notice in the Description page of Project Settings.


#include "CarVehicle.h"

ACarVehicle::ACarVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACarVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void ACarVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
