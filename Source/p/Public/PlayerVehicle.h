// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "PlayerVehicle.generated.h"

/**
 * 
 */
UCLASS()
class P_API APlayerVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	APlayerVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: 
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class USceneComponent* cameraRoot;
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UCameraComponent* playerCamera;
	UPROPERTY(VisibleAnywhere, Category=SteeringWheel)
	class USceneComponent* steeringWheelRoot;
	UPROPERTY(VisibleAnywhere, Category=SteeringWheel)
	class UStaticMeshComponent* steeringWheel;
	UPROPERTY(VisibleAnywhere, Category = SteeringWheel)
	class UArrowComponent* steeringWheelLeft;
	UPROPERTY(VisibleAnywhere, Category = SteeringWheel)
	class UArrowComponent* steeringWheelRight;
	UPROPERTY(VisibleAnywhere, Category=SteeringWheel)
	class USphereComponent* wheelLeftCollision;
	UPROPERTY(VisibleAnywhere, Category = SteeringWheel)
	class USphereComponent* wheelRightCollision;

	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class UMotionControllerComponent* leftController;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class USkeletalMeshComponent* leftHand;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
		class UStaticMeshComponent* leftVisibleHand;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class UMotionControllerComponent* rightController;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class USkeletalMeshComponent* rightHand;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
		class UStaticMeshComponent* rightVisibleHand;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class UGrabRightActorComponent* grabRightComp;
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
	class UGrabLeftActorComponent* grabLeftComp;

	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UWidgetComponent* widgetComp;
	UPROPERTY(EditAnywhere, Category=Setting)  
	TSubclassOf<UUserWidget> widgetFactory;

	UPROPERTY(EditAnywhere, category=Setting)
	class UPlayerMove* playerMove;
	UPROPERTY(BlueprintReadWrite)
	FString objName;
	UPROPERTY(BlueprintReadWrite)
	float objValueLeft;
	UPROPERTY(BlueprintReadWrite)
	float objValueRight;
	UPROPERTY(BlueprintReadWrite)
		float moveValue;


	UPROPERTY(BlueprintReadWrite)
	bool IsGripRight = false;
};
