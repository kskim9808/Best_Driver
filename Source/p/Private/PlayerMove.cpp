// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PlayerVehicle.h"
#include <WheeledVehicleMovementComponent.h>

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	player= Cast<APlayerVehicle>(GetOwner());

	// ��� ����Ʈ ���÷��� ��ġ�� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotate, hmdLocation);

	// HMD ��ġ�� �������� �ٴ����� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	// HMD ��ġ�� ��ġ�� �ʱ�ȭ�ϱ�
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

}


// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (player->IsGripLeft && player->IsGripRight)
	{
	player->GetVehicleMovement()->SetSteeringInput((player->objValueRight / 90.f) * moveSpeed);
		
	}
	else if (player->IsGripRight && !(player->IsGripLeft))
	{
	player->GetVehicleMovement()->SetSteeringInput((player->objValueRight / 90.f) * moveSpeed);
		
	}
	else if (player->IsGripLeft && !(player->IsGripRight))
	{
		player->GetVehicleMovement()->SetSteeringInput((player->objValueLeft / 90.f) * moveSpeed);
		
	}
	else if (!(player->IsGripLeft) && !(player->IsGripRight))
	{
		player->GetVehicleMovement()->SetSteeringInput(0);
	}
	// ...
}

void UPlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &UPlayerMove::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &UPlayerMove::MoveRight);

	PlayerInputComponent->BindAction("HMDReset", IE_Pressed, this, &UPlayerMove::ResetHMD);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &UPlayerMove::BrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &UPlayerMove::BrakeReleased);

}

void UPlayerMove::MoveForward(float value)
{
	if (player == nullptr)
	{
		return;
	}
	player->moveValue = value;

	player->GetVehicleMovement()->SetThrottleInput(value * moveSpeed);

}

void UPlayerMove::MoveRight(float value)
{
	if (player == nullptr)
	{
		return;
	}
}

void UPlayerMove::BrakePressed()
{
	if (player == nullptr)
	{
		return;
	}

	player->GetVehicleMovement()->SetHandbrakeInput(true);
}

void UPlayerMove::BrakeReleased()
{
	if (player == nullptr)
	{
		return;
	}
	player->GetVehicleMovement()->SetHandbrakeInput(false);
}

void UPlayerMove::ResetHMD()
{
	
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

