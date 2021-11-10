// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCourse.h"

// Sets default values
APlayerCourse::APlayerCourse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCourse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCourse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

