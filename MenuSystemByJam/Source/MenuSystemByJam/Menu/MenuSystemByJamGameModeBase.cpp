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
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameModeBase, All, All);

AMenuSystemByJamGameModeBase::AMenuSystemByJamGameModeBase()
{
	HUDClass = AMSBJMenuHUD::StaticClass();
	PlayerControllerClass = AMSBJMenuController::StaticClass();
}

void AMenuSystemByJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	this->UserSettings = UGameUserSettings::GetGameUserSettings();
	this->GameInstance = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	
	checkf(this->UserSettings, TEXT("User Settings is nullptr"));
	checkf(this->GameInstance, TEXT("Game instance is nullptr"));

	this->StartPlayGameModeSettings();
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

void AMenuSystemByJamGameModeBase::StartPlayGameModeSettings()
{
	if (this->GameInstance->GetCurrentLanguage() == "ru-RU")
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("ru-RU"), false);
	else
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("en"), false);
	this->UserSettings->SetFullscreenMode(this->GameInstance->GetCurrentWindowMode());
	this->UserSettings->SetScreenResolution(this->GameInstance->GetScreenViewport());
	this->UserSettings->ApplySettings(false);
}
