// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MSBJMenuController.h"

void AMSBJMenuController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
