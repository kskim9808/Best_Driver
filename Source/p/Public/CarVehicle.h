// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "CarVehicle.generated.h"

/**
 * 
 */
UCLASS()
class P_API ACarVehicle : public AWheeledVehicle
{
	GENERATED_BODY()
public:
	ACarVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	UPROPERTY(EditAnywhere, Category=Setting)
	class ARoadSpline* currentPath;
};
