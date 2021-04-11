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
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameModeBase, All, All);

AMenuSystemByJamGameModeBase::AMenuSystemByJamGameModeBase()
{
	HUDClass = AMSBJMenuHUD::StaticClass();
	PlayerControllerClass = AMSBJMenuController::StaticClass();
}

void AMenuSystemByJamGameModeBase::StartPlay()
{
	Super::StartPlay();
	this->SetStartPlaySettings();
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

void AMenuSystemByJamGameModeBase::SetStartPlaySettings()
{
	const auto UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		UE_LOG(LogMSBJGameModeBase, Error, TEXT("User Settings is nullptr"));
		return;
	}
	UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
	UserSettings->ApplySettings(false);

	const auto DefaultLanguagePlayer = UKismetSystemLibrary::GetDefaultLanguage();
	if (DefaultLanguagePlayer == "en")
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("en"), false);
	else
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("ru-RU"), false);
}
