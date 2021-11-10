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

	// 헤드 마운트 디스플레이 장치의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotate, hmdLocation);

	// HMD 장치의 기준점을 바닥으로 설정하기
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	// HMD 장치의 위치를 초기화하기
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

}


// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// 양손으로 Grip 시 오른손으로 움직인 핸들방향의 정도를 기준으로 steering 값을 넣어주고
	// 왼손으로 Grip 시 왼손기준 오른손으로 Grip 시 오른손 기준
	// 모두 아닐 시 0값으로 넣어줌 
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
// 전진
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

// 브레이크
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

// 플레이어 vr 카메라 위치 초기화
void UPlayerMove::ResetHMD()
{
	
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

