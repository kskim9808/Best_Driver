// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "PlayerPawn.h"
#include "HeadMountedDisplayFunctionLibrary.h"

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

	player= Cast<APlayerPawn>(GetOwner());

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

	// ...
}

void UPlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &UPlayerMove::MoveHorizontal);
	PlayerInputComponent->BindAxis("MoveForward", this, &UPlayerMove::MoveVertical);

	PlayerInputComponent->BindAction("HMDReset", IE_Pressed, this, &UPlayerMove::ResetHMD);

}

void UPlayerMove::MoveHorizontal(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorRightVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void UPlayerMove::MoveVertical(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorForwardVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void UPlayerMove::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

