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

	// TimeToNextCameraChange가 0이 될 때까지 Tick당 시간을 줄여줌
	TimeToNextCameraChange -= DeltaTime;

	// 0초 이하라면
	if (TimeToNextCameraChange <= 0.0f)
	{
		// 2초 더해줌
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// 0번 컨트롤러 찾기
		APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayer)
		{
			// 0번 카메라가 참조하는 카메라 체크
			if (CameraTwo && (OurPlayer->GetViewTarget() == CameraOne))
			{
				// 2번 카메라로 부드럽게 화면 전환
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

