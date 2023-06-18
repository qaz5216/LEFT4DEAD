// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Elevator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMOVE_API AElevator : public AWeapon
{
	GENERATED_BODY()
public:
	AElevator();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool ispress;
};
