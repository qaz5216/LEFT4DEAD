// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

AElevator::AElevator()
{
	
	ispress = false;
}

void AElevator::pressing()
{
	ispress = true;
	if (ispress)
	{
		UE_LOG(LogTemp, Log, TEXT("pressing"));
	}
}