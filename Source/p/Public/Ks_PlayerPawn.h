// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ks_PlayerPawn.generated.h"

UCLASS()
class P_API AKs_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKs_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere, Category = Setting)
	class USkeletalMeshComponent* bodyMesh;

	UPROPERTY(VisibleAnywhere, Category = Setting)
	class USceneComponent* cameraRoot;
	UPROPERTY(VisibleAnywhere, Category = Setting)
	class UCameraComponent* playerCamera;

	UPROPERTY(EditAnywhere, category = Setting)
	class UPlayerMove* playerMove;


	UPROPERTY(EditAnywhere, category = Setting)
	class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, category = Setting)
	class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, category = Setting)
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, category = Setting)
	class USkeletalMeshComponent* leftHand;

};
