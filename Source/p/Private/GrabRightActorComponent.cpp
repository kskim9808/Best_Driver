// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabRightActorComponent.h"
#include "PlayerVehicle.h"
#include <Components/SphereComponent.h>
#include <DrawDebugHelpers.h>
#include <Components/ArrowComponent.h>

// Sets default values for this component's properties
UGrabRightActorComponent::UGrabRightActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabRightActorComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerVehicle>(GetOwner());
	
}


// Called every frame
void UGrabRightActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawGrabLine();
	
}

void UGrabRightActorComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &UGrabRightActorComponent::GrabAction);
	PlayerInputComponent->BindAction("RightGrip", IE_Released, this, &UGrabRightActorComponent::ReleaseAction);
}

void UGrabRightActorComponent::DrawGrabLine()
{

	FHitResult hitInfo;
	FVector startPos = player->rightHand->GetComponentLocation();

	// 물리 객체와 동적 객체에 대해서 충돌 체크
	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	// 플레이어 액터는 무시
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredComponent(player->GetMesh());
	queryParams.AddIgnoredComponent(player->leftHand);
	queryParams.AddIgnoredComponent(player->leftHand);
	queryParams.AddIgnoredComponent(player->wheelLeftCollision);
	queryParams.AddIgnoredComponent(player->steeringWheel);

	if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(15.0f), queryParams))
	{
		grabObject = hitInfo;
	}
	else
	{
		grabObject = FHitResult();
	}
// 	if (grabObject.GetComponent() != nullptr)
// 	{
// 		player->objName = grabObject.GetComponent()->GetName();
// 	}
	//DrawDebugSphere(GetWorld(), startPos, 15.f, 30, FColor::Green, false, -1, 0, 1);
}



void UGrabRightActorComponent::GrabAction()
{
	if (grabObject.GetComponent() == player->wheelRightCollision)
	{
		FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		grabObject.GetComponent()->SetSimulatePhysics(false);
		grabObject.GetComponent()->AttachToComponent(player->rightHand, attachRules, TEXT("GrabPoint"));
		grabObject.GetComponent()->SetEnableGravity(false);
		player->rightHand->SetVisibility(false);
		player->rightVisibleHand->SetVisibility(true);
		player->rightTutorialHand->SetVisibility(false);
		player->IsGripRight = true;

	}
}

void UGrabRightActorComponent::ReleaseAction()
{
	player->wheelRightCollision->SetEnableGravity(true);
	player->wheelRightCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	player->rightHand->SetVisibility(true);
	player->wheelRightCollision->SetWorldLocation(player->steeringWheelRight->GetComponentLocation());
	player->rightHand->SetVisibility(true);
	player->rightVisibleHand->SetVisibility(false);
	player->rightTutorialHand->SetVisibility(true);
	player->IsGripRight = false;

}
