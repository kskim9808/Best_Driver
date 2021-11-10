// Fill out your copyright notice in the Description page of Project Settings.


#include "Traffic.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include "OtherWheeledVehicle.h"
#include <Kismet/KismetSystemLibrary.h>
#include <WheeledVehicleMovementComponent.h>
#include <Components/RectLightComponent.h>
#include "PlayerVehicle.h"
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>



// Sets default values
ATraffic::ATraffic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	// 차량신호등 메쉬
	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetupAttachment(boxComp);
	// 차량신호등 빨간불
	redRight = CreateDefaultSubobject<URectLightComponent>(TEXT("RedRight"));
	redRight->SetupAttachment(boxComp);
	redRight->Intensity = 150.f;
	redRight->LightColor.R = 255.f;
	redRight->LightColor.G = 0.f;
	redRight->LightColor.B = 0.f;
	// 차량신호등 노란불
	yellowRight = CreateDefaultSubobject<URectLightComponent>(TEXT("YellowRight"));
	yellowRight->SetupAttachment(boxComp);
	yellowRight->Intensity = 150.f;
	yellowRight->LightColor.R = 255.f;
	yellowRight->LightColor.G = 137.f;
	yellowRight->LightColor.B = 0.f;
	// 차량신호등 왼쪽이동 초록불
	greenLTurnRight = CreateDefaultSubobject<URectLightComponent>(TEXT("GreenLTurnRight"));
	greenLTurnRight->SetupAttachment(boxComp);
	greenLTurnRight->Intensity = 150.f;
	greenLTurnRight->LightColor.R = 0.f;
	greenLTurnRight->LightColor.G = 255.f;
	greenLTurnRight->LightColor.B = 150.f;
	// 차량신호등 초록불
	greenRight = CreateDefaultSubobject<URectLightComponent>(TEXT("GreenRight"));
	greenRight->SetupAttachment(boxComp);
	greenRight->Intensity = 150.f;
	greenRight->LightColor.R = 0.f;
	greenRight->LightColor.G = 255.f;
	greenRight->LightColor.B = 150.f;

}

// Called when the game starts or when spawned
void ATraffic::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ATraffic::TrafficRedOverlap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &ATraffic::TrafficRedEndOverlap);
}

// Called every frame
void ATraffic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 초록불엔 노콜리전
	// 빨간불이나 노란불 시 충돌체 적용 
	if (greenRight->IsVisible() == true)
	{
		boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		boxComp->SetCollisionProfileName(TEXT("Traffic"));

	}
}
// 해당 충돌체에 AI차량이 오버랩시 해당 차량 멈춤
void ATraffic::TrafficRedOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto aiCar = Cast<AOtherWheeledVehicle>(OtherActor);
	//auto player = Cast<APlayerVehicle>(OtherActor);
	if (aiCar)
	{
		aiCar->Stop();
	}

	/*if (player && playerCnt == 1 && yellowRight->IsVisible() == true)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
		player->widgetComp->SetVisibility(true);
		if (widgetFactory)
		{
			player->widgetComp->SetWidgetClass(widgetFactory);
		}
		playerCnt--;
		
		FTimerHandle moveTIme;
		GetWorld()->GetTimerManager().SetTimer(moveTIme, this, &ATraffic::Move, 0.1f, false);
	}*/
}
// 오버랩 끝날시 다시 움직임
void ATraffic::TrafficRedEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto aiCar = Cast<AOtherWheeledVehicle>(OtherActor);
	if (aiCar)
	{
		aiCar->Move();
	}
}

/*
void ATraffic::Move()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}*/

