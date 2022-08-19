// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraUtility.h"
#include "kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCameraUtility::UCameraUtility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraUtility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCameraUtility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;

	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* OurPlayer = UGameplayStatics::GetPlayerController(this, 0); // 플레이어 일시 중지

		if (OurPlayer)
		{
			// 카메라2가 카메라2인 경우
			if (CameraTwo && (OurPlayer->GetViewTarget() == CameraOne))
			{
				OurPlayer->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
			else if (CameraOne)
			{
				OurPlayer->SetViewTarget(CameraOne);
			}

		}
	}
}

