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

	tBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root")); // UBoxComponent ���� ��� ����
	//tBox->bGenerateOverlapEvents = true; // ��ø �̺�Ʈ ����
	tBox->SetGenerateOverlapEvents(true); // ��ø �̺�Ʈ ����
	tBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnOverlap);
	//tBox->SetRelativeScale3D(BoxSize); // ���� ũ�� ����

	RootComponent = tBox;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh")); // ���� �޽�

	// ��Ʈ ���� ��ҿ� ÷��
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

	FVector NewLocation = GetActorLocation(); // ������ ���� ��ġ
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		// Sin�� �̿��ϸ� -1 ~ 1 ������ �����ϴ� ���� ���� �� ����


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
	// �÷��̾ ���� �¾��� ��, ó�� �ڸ��� �̵�
	OtherActor->SetActorLocation(PlayerStartingLocation);
}

void AMyActor::OnOverlap(UPrimitiveComponent* OverlappingComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AddDebugMessage();

	// �÷��̾ ���� �¾��� ��, ó�� �ڸ��� �̵�
	if (OtherActor->IsA(ACharacter::StaticClass()))
		OtherActor->SetActorLocation(PlayerStartingLocation);
}

void AMyActor::AddDebugMessage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "hehe");
}

