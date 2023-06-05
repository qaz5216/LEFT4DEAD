// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectMoveGameModeBase.h"

void AProjectMoveGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// 디버그 메시지를 5 초간 표시합니다.
	  // "키" (첫 번째 인수) 값을 -1 로 하면 이 메시지를 절대 업데이트하거나 새로고칠 필요가 없음을 나타냅니다.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
}