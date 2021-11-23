// Fill out your copyright notice in the Description page of Project Settings.


#include "CitizenAnimInstance.h"
#include <Animation/AnimMontage.h>

void UCitizenAnimInstance::Die()
{
	Montage_Play(dieMontage);
}

void UCitizenAnimInstance::OnDieMontageEnded(UAnimMontage* animMontage, bool isEnd)
{
	TryGetPawnOwner()->Destroy();
}
