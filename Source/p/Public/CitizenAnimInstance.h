// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CitizenFSM.h"
#include "CitizenAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class P_API UCitizenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadOnly)
	EEnemyState state;

	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadOnly)
	class UAnimMontage* dieMontage;

public:
	void Die();

	UFUNCTION()
	void OnDieMontageEnded(UAnimMontage* animMontage, bool isEnd);
};
