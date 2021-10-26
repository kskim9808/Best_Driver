// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Traffic.generated.h"

UCLASS()
class P_API ATraffic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraffic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TrafficRedOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TrafficRedEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UStaticMeshComponent* bodyMesh;
	UPROPERTY(VisibleAnywhere, Category=Setting)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category = LightSetting)
	class URectLightComponent* redRight;
	UPROPERTY(VisibleAnywhere, Category = LightSetting)
	class URectLightComponent* yellowRight;
	UPROPERTY(VisibleAnywhere, Category = LightSetting)
	class URectLightComponent* greenLTurnRight;
	UPROPERTY(VisibleAnywhere, Category = LightSetting)
	class URectLightComponent* greenRight;
};
