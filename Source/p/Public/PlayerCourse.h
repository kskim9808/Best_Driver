// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCourse.generated.h"

UCLASS()
class P_API APlayerCourse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCourse();

	//virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = Setting)
	class USplineComponent* spline;
 	/*UPROPERTY(EditAnywhere, Category = Setting)
	class USplineMeshComponent* bodyMesh;

	UPROPERTY()
	float sigment;
	UPROPERTY()
	int lastIndex;*/
};
