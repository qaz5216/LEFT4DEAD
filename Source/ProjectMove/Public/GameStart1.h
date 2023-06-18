// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStart1.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMOVE_API UGameStart1 : public UUserWidget
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere,meta=(BindWidget))
		class UButton* BtnStart2;
};
