// Copyright Epic Games, Inc. All Rights Reserved.


#include "MenuSystemByJamGameModeBase.h"
#include "HUD/MSBJMenuHUD.h"
#include "HUD/MSBJMenuController.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameModeBase, All, All);

AMenuSystemByJamGameModeBase::AMenuSystemByJamGameModeBase()
{
	HUDClass = AMSBJMenuHUD::StaticClass();
	PlayerControllerClass = AMSBJMenuController::StaticClass();
}

void AMenuSystemByJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	const auto UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		UE_LOG(LogMSBJGameModeBase, Error, TEXT("User Settings is nullptr"));
		return;
	}
	UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	UserSettings->ApplySettings(false);
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
