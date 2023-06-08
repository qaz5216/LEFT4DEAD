// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMOVE_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	protected:
		// ȭ�� �߾ӿ� �׷���
		UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;
	public:
		//HUD �� ���� �ֿ� ��� ���Դϴ�.
		virtual void DrawHUD() override;
		
};
