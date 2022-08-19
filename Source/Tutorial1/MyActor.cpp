// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial1.h"
#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "LandscapeProxy.h"
#include "GameFramework/Character.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	tBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root")); // UBoxComponent 구성 요소 생성
	//tBox->bGenerateOverlapEvents = true; // 중첩 이벤트 생성
	tBox->SetGenerateOverlapEvents(true); // 중첩 이벤트 생성
	tBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnOverlap);
	//tBox->SetRelativeScale3D(BoxSize); // 상자 크기 변경

	RootComponent = tBox;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh")); // 정적 메쉬

	// 루트 구성 요소에 첨부
	MyMesh->AttachTo(RootComponent);

	SpeedScale = 0.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation(); // 액터의 현재 위치
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		// Sin을 이용하면 -1 ~ 1 사이의 변동하는 값을 얻을 수 있음


	if (bMovesYAxis)
		NewLocation.Y += DeltaHeight * SpeedScale;
	if (bMovesYAxis)
		NewLocation.X += DeltaHeight * SpeedScale;


	//NewLocation.Z += DeltaHeight * 20.0f;
	NewLocation.Y += DeltaHeight * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void AMyActor::TriggerEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// 플레이어가 공에 맞았을 때, 처음 자리로 이동
	OtherActor->SetActorLocation(PlayerStartingLocation);
}

void AMyActor::OnOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AddDebugMessage();

	// 플레이어가 공에 맞았을 때, 처음 자리로 이동
	if (OtherActor->IsA(ACharacter::StaticClass()))
		OtherActor->SetActorLocation(PlayerStartingLocation);
}

void AMyActor::AddDebugMessage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "hehe");
}

