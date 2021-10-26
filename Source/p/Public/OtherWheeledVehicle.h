// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "OtherWheeledVehicle.generated.h"

/**
 * 
 */
UCLASS()
class P_API AOtherWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()
	
public:
	AOtherWheeledVehicle();

private:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	float GetPath();

	void Stop();
	
	void Move();
	
	UFUNCTION()
	void OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, Category = Setting)
	class ARoadSpline* path1;
	UPROPERTY(EditAnywhere, Category = Setting)
	TArray<class ARoadSpline*> arrPath;
	UPROPERTY(EditAnywhere, Category = Setting)
	float speed = 0.6f;
	UPROPERTY(EditAnywhere, Category = Setting)
	int pathNum = 0;

	bool stand = false;
};
