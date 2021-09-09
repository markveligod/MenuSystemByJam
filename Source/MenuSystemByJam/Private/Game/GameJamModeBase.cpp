// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameJamModeBase.h"
#include "Menu/MSBJGameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"

AGameJamModeBase::AGameJamModeBase()
{

}

void AGameJamModeBase::StartPlay()
{
	Super::StartPlay();
	checkf(GetWorld(), TEXT("World is nullptr"));
	this->GameInst = Cast<UMSBJGameInstance>(GetGameInstance());
	checkf(this->GameInst, TEXT("Game instance is nullptr"));
	this->UserSettings = UGameUserSettings::GetGameUserSettings();
	checkf(this->UserSettings, TEXT("User settings is nullptr"));

	this->SetupStartLevelSettings();
	this->ChangeGameState(EGameLevelState::GameOver);
}

void AGameJamModeBase::ChangeGameState(EGameLevelState NewState)
{
	if (this->CurrentGameState == NewState)
		return;
	this->CurrentGameState = NewState;
	this->OnGameLevelStateChanged.Broadcast(NewState);
}

void AGameJamModeBase::SetupStartLevelSettings()
{
	UKismetInternationalizationLibrary::SetCurrentCulture(this->GameInst->GetCurrentLanguage(), false);
	this->UserSettings->SetFullscreenMode(this->GameInst->GetCurrentWindowMode());
	this->UserSettings->SetScreenResolution(this->GameInst->GetScreenViewport());
	this->UserSettings->SetAntiAliasingQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetAudioQualityLevel(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetFoliageQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetPostProcessingQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetShadingQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetShadowQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetTextureQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetViewDistanceQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->SetVisualEffectQuality(this->GameInst->GetCurrentQualityValue());
	this->UserSettings->ApplySettings(false);
}
