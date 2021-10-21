// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICon_Driver.generated.h"

/**
 * 
 */
UCLASS()
class P_API AAICon_Driver : public AAIController
{
	GENERATED_BODY()

public:
	AAICon_Driver();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void GetPawn();

	UFUNCTION(BlueprintCallable)
	void Drive();
	
	void Steering();
	
	void SplineDrive();
	
	 float GetDistanceAlongSpline();

	void SetUpSpline(class ARoadSpline* currentPathReference);
	
	FVector GetSplinePosition();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDriving();
public:
	UPROPERTY()
	class ACarVehicle* controlledCar;
	UPROPERTY()
	class ARoadSpline* currentPath;
	
	float distanceAlongCurrentSpline;
	float distanceToPushLength = 500.f;
	float setCurrentSplineLength;
	float splinePushSpeed = 300.f;

	UPROPERTY(BlueprintReadWrite)
	float Loc;
	UPROPERTY(BlueprintReadWrite)
	FVector endLoc;
};
