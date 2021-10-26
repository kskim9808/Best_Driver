// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KS_startPawn.generated.h"

UCLASS()
class P_API AKS_startPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKS_startPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=Setting)
	class USkeletalMeshComponent* skeletaMesh;
	UPROPERTY(VisibleAnywhere, Category = Setting)
		class USceneComponent* cameraRoot;
	UPROPERTY(VisibleAnywhere, Category = Setting)
		class UCameraComponent* playerCamera;


};
