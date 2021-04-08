// Copyright Epic Games, Inc. All Rights Reserved.


#include "MenuSystemByJamGameModeBase.h"
#include "HUD/MSBJMenuHUD.h"
#include "HUD/MSBJMenuController.h"

AMenuSystemByJamGameModeBase::AMenuSystemByJamGameModeBase()
{
	HUDClass = AMSBJMenuHUD::StaticClass();
	PlayerControllerClass = AMSBJMenuController::StaticClass();
}

void AMenuSystemByJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	this->SetGameState(this->CurrentState);
}

const EMSBJGameMenuState& AMenuSystemByJamGameModeBase::GetCurrentState() const
{
	return (this->CurrentState);
}

void AMenuSystemByJamGameModeBase::SetGameState(EMSBJGameMenuState NewState)
{
	this->CurrentState = NewState;
	this->OnGameMenuStateChangedSignature.Broadcast(NewState);
}
