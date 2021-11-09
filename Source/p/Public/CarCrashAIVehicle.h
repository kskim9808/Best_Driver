// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "CarCrashAIVehicle.generated.h"

/**
 * 
 */
UCLASS()
class P_API ACarCrashAIVehicle : public AWheeledVehicle
{
	GENERATED_BODY()
public:
	ACarCrashAIVehicle();

private:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	float GetPath();
	UFUNCTION(BlueprintCallable)
	void Stop();

	void Move();
public:
	UPROPERTY(VisibleAnywhere, Category = Setting)
		class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class ARoadSpline* path1;

	UPROPERTY(EditAnywhere, Category = Setting)
		float speed = 0.9f;
};
