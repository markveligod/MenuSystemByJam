// Copyright Epic Games, Inc. All Rights Reserved.

/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "MenuSystemByJamGameModeBase.h"
#include "HUD/MSBJMenuHUD.h"
#include "HUD/MSBJMenuController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MSBJGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameModeBase, All, All);

AMenuSystemByJamGameModeBase::AMenuSystemByJamGameModeBase()
{
	HUDClass = AMSBJMenuHUD::StaticClass();
	PlayerControllerClass = AMSBJMenuController::StaticClass();
}

void AMenuSystemByJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	this->GameInstance = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	
	checkf(this->GameInstance, TEXT("Game instance is nullptr"));
	
	this->GameInstance->RunCurrentUserSettings();
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

