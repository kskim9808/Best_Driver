// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include <VehicleAnimInstance.h>
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
	UFUNCTION(BlueprintCallable)
	void Stop();
	
	void Move();
	
	void Spawn();

	UFUNCTION()
	void OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Setting)
	class ARoadSpline* path1;
	/*UPROPERTY(EditAnywhere, Category = Setting)
	TArray<class ARoadSpline*> arrPath;*/
	UPROPERTY(EditAnywhere, Category = Setting)
	float speed = 0.6f;
	/*UPROPERTY(EditAnywhere, Category = Setting)
	int pathNum = 0;*/

	UPROPERTY(EditAnywhere, Category=Setting)
	TArray<class USkeletalMesh*> cars;

	UPROPERTY(EditAnywhere, Category = Setting)
	TArray<TSubclassOf<UVehicleAnimInstance>> carAnimation;

	UPROPERTY(VisibleAnywhere, Category=Setting)
	int carNum;
	bool stand = false;
};
