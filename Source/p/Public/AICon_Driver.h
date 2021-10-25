// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICon_Driver.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FGate
{	
	GENERATED_BODY()
public:
	FORCEINLINE FGate();
	explicit FORCEINLINE FGate(bool bStartClosed);

	FORCEINLINE void Open() { bGateOpen = true; }
	FORCEINLINE void Close() { bGateOpen = false; }
	FORCEINLINE void Toggle() { bGateOpen = !bGateOpen; }
	FORCEINLINE bool IsOpen() const { return bGateOpen; }
private:
	UPROPERTY(VisibleAnywhere)
		bool bGateOpen;
};
FORCEINLINE FGate::FGate() : bGateOpen(true)
{}
FORCEINLINE FGate::FGate(const bool bStartClosed) : bGateOpen(!bStartClosed)
{}

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
	
	float Steering();
	
	void SplineDrive();

	UFUNCTION(BlueprintPure)
	float GetDistanceAlongSpline();

	void SetUpSpline(class ARoadSpline* currentPathReference);
	
	FVector GetSplinePosition();

	UFUNCTION()
	void StartDriving();
public:
	UPROPERTY(BlueprintReadWrite)
	class ACarVehicle* controlledCar;
	UPROPERTY(BlueprintReadWrite)
	class ARoadSpline* currentPath;

	float distanceAlongCurrentSpline;
	float distanceToPushLength = 400.f;
	float currentSplineLength;
	float splinePushSpeed = 100.f;
	UPROPERTY(BlueprintReadWrite)
	float currentThrottleInput;
	FVector splinePosition;
	UPROPERTY(BlueprintReadWrite)
	float Loc;
	UPROPERTY(BlueprintReadWrite)
	float length;
	UPROPERTY(BlueprintReadWrite)
	FVector endLoc;

	UPROPERTY(VisibleAnywhere)
	FGate Gate;
};
