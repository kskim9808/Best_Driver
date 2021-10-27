// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class P_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Spawn();
public:
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class USceneComponent* spawnRoot;
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UArrowComponent* spawnPosition;
	UPROPERTY(EditAnywhere, Category=Setting)
	TSubclassOf<class AOtherWheeledVehicle> spawnFactory;
	UPROPERTY(EditAnywhere, Category = Setting)
	class ARoadSpline* path;
	UPROPERTY(VisibleAnywhere, Category = Setting)
	bool spawned;
};
