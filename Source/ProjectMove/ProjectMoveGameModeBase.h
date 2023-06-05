// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectMoveGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMOVE_API AProjectMoveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};
