// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabRightActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P_API UGrabRightActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabRightActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
	void DrawGrabLine();
	void GrabAction();
	void GrabGripAction();
	void ReleaseAction();
	void ReleaseGripAction();
public:
	UPROPERTY(VisibleAnywhere, Category=player)
	class APlayerVehicle* player;

	UPROPERTY()
	FHitResult grabObject;

};
