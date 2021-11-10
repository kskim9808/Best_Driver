// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include <Components/ArrowComponent.h>
#include "OtherWheeledVehicle.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	spawnRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnRoot"));
	RootComponent = spawnRoot;
	spawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPosition"));
	spawnPosition->SetupAttachment(spawnRoot);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::Spawn()
{
	// 스폰이 이미 된 상황 이면 리턴
	// 스폰 아직 안됐다면 OtherWheeledVehicle 스폰
	// 스폰시 spawnFactory에서 지정해준 해당 path(길)을 중심으로 이동
	if (spawned)
	{
		return;
	}
	else
	{
		if (spawnFactory) 
		{
			auto cars = GetWorld()->SpawnActor<AOtherWheeledVehicle>(spawnFactory, GetActorTransform());
			spawned = true;
			auto car = Cast<AOtherWheeledVehicle>(cars);
			if (car)
			{
				car->path1 = path;
			}
		}
		Spawn();
	}
}

