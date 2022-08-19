// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraUtilityActor.h"
#include "kismet/GameplayStatics.h"

// Sets default values
ACameraUtilityActor::ACameraUtilityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraUtilityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraUtilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	// TimeToNextCameraChange�� 0�� �� ������ Tick�� �ð��� �ٿ���
	TimeToNextCameraChange -= DeltaTime;

	// 0�� ���϶��
	if (TimeToNextCameraChange <= 0.0f)
	{
		// 2�� ������
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// 0�� ��Ʈ�ѷ� ã��
		APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayer)
		{
			// 0�� ī�޶� �����ϴ� ī�޶� üũ
			if (CameraTwo && (OurPlayer->GetViewTarget() == CameraOne))
			{
				// 2�� ī�޶�� �ε巴�� ȭ�� ��ȯ
				OurPlayer->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				//OurPlayer->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);

				OurPlayer->SetViewTarget(CameraOne);
			}

		}
	}
}

