// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCourse.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
APlayerCourse::APlayerCourse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = spline;

}


/*
void APlayerCourse::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	lastIndex = UKismetMathLibrary::FTrunc(spline->GetSplineLength() / UKismetMathLibrary::Clamp(500.f, 50.f, 100000.f));
	sigment = spline->GetSplineLength() / (lastIndex + 1);


	for (int i = 0; i < lastIndex; i++)
	{
		bodyMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		static ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/Moon/Mesh/SM_PlayerCourse.SM_PlayerCourse"));
		if (meshAsset.Succeeded())
		{
			bodyMesh->SetStaticMesh(meshAsset.Object);
		}
		auto startPos = spline->GetLocationAtDistanceAlongSpline(sigment * i, ESplineCoordinateSpace::Local);
		auto startTangent = UKismetMathLibrary::ClampVectorSize(spline->GetTangentAtDistanceAlongSpline(sigment * i, ESplineCoordinateSpace::Local), 0, sigment);
		auto startScale = spline->GetScaleAtDistanceAlongSpline(sigment * i).Y;
		auto endPos = spline->GetLocationAtDistanceAlongSpline(sigment * (i + 1), ESplineCoordinateSpace::Local);
		auto endTangent = UKismetMathLibrary::ClampVectorSize(spline->GetTangentAtDistanceAlongSpline(sigment * (i + 1), ESplineCoordinateSpace::Local), 0, sigment);
		auto endScale = spline->GetScaleAtDistanceAlongSpline(sigment * (i + 1)).Y;
		bodyMesh->SetStartAndEnd(startPos, startTangent, endPos, endTangent);
		bodyMesh->SetStartScale(FVector2D(startScale * 0.5f, startScale * 0.5f * 1.f));
		bodyMesh->SetEndScale(FVector2D(endScale * 0.5f, endScale * 0.5f * 1.f));
	}
}*/

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



