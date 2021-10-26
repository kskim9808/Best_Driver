// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void MoveForward(float value);
	void MoveRight(float value);
	void BrakePressed();
	void BrakeReleased();
	
	class APlayerVehicle* player;

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float moveSpeed = 0.8f;

	void ResetHMD();

	FRotator hmdRotate;
	FVector hmdLocation;
		
};
