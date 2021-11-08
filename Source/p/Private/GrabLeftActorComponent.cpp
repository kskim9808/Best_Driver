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
	objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	// 플레이어 액터는 무시
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredComponent(player->GetMesh());
	queryParams.AddIgnoredComponent(player->rightHand);
	queryParams.AddIgnoredComponent(player->steeringWheel);

	if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(20.0f), queryParams))
	{
		grabObject = hitInfo;
	}
	else
	{
		grabObject = FHitResult();
	}
	if (grabObject.GetComponent() != nullptr)
	{
		player->objName = grabObject.GetComponent()->GetName();
	}
	//DrawDebugSphere(GetWorld(), startPos, 10.f, 30, FColor::Green, false, -1, 0, 1);
}

void UGrabLeftActorComponent::GrabAction()
{
	if (grabObject.GetComponent() == player->wheelLeftCollision)
	{
		FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		grabObject.GetComponent()->SetSimulatePhysics(false);
		grabObject.GetComponent()->AttachToComponent(player->leftHand, attachRules, TEXT("GrabPoint"));
		grabObject.GetComponent()->SetEnableGravity(false);
		player->leftHand->SetVisibility(false);
		player->leftVisibleHand->SetVisibility(true);
	}
}

void UGrabLeftActorComponent::ReleaseAction()
{
	player->wheelLeftCollision->SetEnableGravity(true);
	player->wheelLeftCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	player->leftHand->SetVisibility(true);
	player->wheelLeftCollision->SetWorldLocation(player->steeringWheelLeft->GetComponentLocation());
	player->leftHand->SetVisibility(true);
	player->leftVisibleHand->SetVisibility(false);

}
