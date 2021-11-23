// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabLeftActorComponent.h"
#include "PlayerVehicle.h"
#include <Components/SphereComponent.h>
#include <DrawDebugHelpers.h>
#include <Components/ArrowComponent.h>

// Sets default values for this component's properties
UGrabLeftActorComponent::UGrabLeftActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabLeftActorComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerVehicle>(GetOwner());

}


// Called every frame
void UGrabLeftActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawGrabLine();
}

void UGrabLeftActorComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UGrabLeftActorComponent::GrabAction);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UGrabLeftActorComponent::ReleaseAction);
}

void UGrabLeftActorComponent::DrawGrabLine()
{

	FHitResult hitInfo;
	FVector startPos = player->leftHand->GetComponentLocation();

	// 물리 객체와 동적 객체에 대해서 충돌 체크
	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	// 무시하고 싶은 컴포넌트 추가
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredComponent(player->GetMesh());
	queryParams.AddIgnoredComponent(player->rightHand);
	queryParams.AddIgnoredComponent(player->wheelRightCollision);
	queryParams.AddIgnoredComponent(player->steeringWheel);
	if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(15.0f), queryParams))
	{
		grabObject = hitInfo;
	}
	else
	{
		grabObject = FHitResult();
	}
// 	TArray<FHitResult> arrHitInfo;
// 	if (GetWorld()->SweepMultiByChannel(arrHitInfo, startPos, startPos, FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeSphere(150.0f), queryParams))
// 	{
// 		grabObjects = arrHitInfo;
// 	}
// 	else
// 	{
// 		grabObjects = TArray<FHitResult>();
// 	}
// 	if (grabObjects.GetData() != nullptr)
// 	{
// 		for (int i = 0; i < grabObjects.Num(); i++)
// 		{
// 		
// 			player->arrObjName[i] = grabObjects[i].GetComponent()->GetName();
// 		}
// 	}
	
	//DrawDebugSphere(GetWorld(), startPos, 15.f, 30, FColor::Green, false, -1, 0, 1);
}

void UGrabLeftActorComponent::GrabAction()
{
	// Grip 을 눌렀을시
	// 만약 Hitresult 된 것이 wheelLeftCollision 이라면
	// 해당 컴포넌트를 leftHand 에 붙힘
	// 붙힐 때 주의점 : 피직스와 중력을 꺼줘야함
	if (grabObject.GetComponent() == player->wheelLeftCollision)
	{
		FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		grabObject.GetComponent()->SetSimulatePhysics(false);
		grabObject.GetComponent()->AttachToComponent(player->leftHand, attachRules, TEXT("GrabPoint"));
		grabObject.GetComponent()->SetEnableGravity(false);
		player->leftHand->SetVisibility(false);
		player->leftVisibleHand->SetVisibility(true);
		player->leftTutorialHand->SetVisibility(false);
		player->IsGripLeft = true;
	}
}

void UGrabLeftActorComponent::ReleaseAction()
{
	// Grip 버튼 릴리즈시 leftHand에서 때주고
	// 빠진 wheelLeftCollision 을 원래 위치에 다시 붙혀줌
	player->wheelLeftCollision->SetEnableGravity(true);
	player->wheelLeftCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	player->leftHand->SetVisibility(true);
	player->wheelLeftCollision->SetWorldLocation(player->steeringWheelLeft->GetComponentLocation());
	player->leftHand->SetVisibility(true);
	player->leftVisibleHand->SetVisibility(false);
	player->leftTutorialHand->SetVisibility(true);

	player->IsGripLeft = false;
}
