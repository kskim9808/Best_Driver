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
	UPROPERTY(VisibleAnywhere, Category = Setting)
	class USceneComponent* cameraRoot;
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UCameraComponent* playerCamera;
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UWidgetComponent* widgetComp;
	UPROPERTY(EditAnywhere, Category = Setting)
	TSubclassOf<UUserWidget> widgetFactory;

	UPROPERTY(EditAnywhere, category=Setting)
	class UPlayerMove* playerMove;

};
