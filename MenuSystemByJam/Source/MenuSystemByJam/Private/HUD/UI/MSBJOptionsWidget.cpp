// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/MSBJOptionsWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "MenuSystemByJam/MenuSystemByJamGameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/ComboBox.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJOptionsWidget, All, All);

void UMSBJOptionsWidget::SetNewScreenSize(int32 X, int32 Y)
{
	const auto UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("User Settings is nullptr"));
		return;
	}
	UserSettings->SetScreenResolution(FIntPoint(X, Y));
	UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (!this->MusicSlider || !this->SoundSlider || !this->BackButton || !this->FullScreenCheckBox)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("Lol NativeOnInitialized is nullptr"));
		return;
	}
	this->MusicSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedMusicSlider);
	this->SoundSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedSoundSlider);
	this->BackButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnComeBack);
	this->FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UMSBJOptionsWidget::OnFullScreenCheck);
}

void UMSBJOptionsWidget::OnChangedMusicSlider(float Value)
{
	int32 TempValue = Value * 100;
	this->MusicValueTextBlock->SetText(FText::FromString(FString::FromInt(TempValue)));
}

void UMSBJOptionsWidget::OnChangedSoundSlider(float Value)
{
	int32 TempValue = Value * 100;
	this->SoundValueTextBlock->SetText(FText::FromString(FString::FromInt(TempValue)));
}

void UMSBJOptionsWidget::OnComeBack()
{
	const auto GameMode = GetCurrentGameMode();
	if (!GameMode)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("Game mode is nullptr"));
		return;
	}

	GameMode->SetGameState(EMSBJGameMenuState::InProgress);
}

void UMSBJOptionsWidget::OnFullScreenCheck(bool bIsChecked)
{
	const auto UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("User Settings is nullptr"));
		return;
	}
	UE_LOG(LogMSBJOptionsWidget, Display, TEXT("Full Screen: %d"), bIsChecked);
	UserSettings->SetFullscreenMode(bIsChecked == true ? EWindowMode::Fullscreen : EWindowMode::Windowed);
	UserSettings->ApplySettings(false);
}
