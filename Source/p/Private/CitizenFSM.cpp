// Fill out your copyright notice in the Description page of Project Settings.


#include "CitizenFSM.h"
#include "CitizenCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "CitizenAnimInstance.h"

// Sets default values for this component's properties
UCitizenFSM::UCitizenFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCitizenFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	me = Cast<ACitizenCharacter>(GetOwner());
	anim = Cast<UCitizenAnimInstance>(me->GetMesh()->GetAnimInstance());
	me->GetCharacterMovement()->MaxWalkSpeed = 600;

}


// Called every frame
void UCitizenFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (m_state)
	{
	case EEnemyState::Idle:
		IdelState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Hit:
		Hitstate();
		break;
	}
}
// 캐릭터 정지상태
void UCitizenFSM::IdelState()
{
	anim->state = m_state;

}
// 캐릭터 이동
void UCitizenFSM::MoveState()
{
	anim->state = m_state;
	FVector dir = me->GetControlRotation().Quaternion().GetForwardVector();
	me->AddMovementInput(dir, 1.f);
}

void UCitizenFSM::Hitstate()
{

}

