/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "HUD/UI/MSBJOptionsWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Sound/SoundClass.h"

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

void UMSBJOptionsWidget::SetQualityGame(int32 NumQuality)
{
	const auto UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("User Settings is nullptr"));
		return;
	}

	UserSettings->SetTextureQuality(NumQuality);
	UserSettings->SetAntiAliasingQuality(NumQuality);
	UserSettings->SetFoliageQuality(NumQuality);
	UserSettings->SetPostProcessingQuality(NumQuality);
	UserSettings->SetShadingQuality(NumQuality);
	UserSettings->SetShadowQuality(NumQuality);
	UserSettings->SetViewDistanceQuality(NumQuality);
	UserSettings->SetVisualEffectQuality(NumQuality);
	
	UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (!this->MusicSlider || !this->SoundSlider || !this->BackButton || !this->FullScreenCheckBox || !this->LangEnButton || !this->LangRuButton)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("Lol NativeOnInitialized is nullptr"));
		return;
	}
	this->MusicSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedMusicSlider);
	this->SoundSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedSoundSlider);
	this->BackButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnComeBack);
	this->FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UMSBJOptionsWidget::OnFullScreenCheck);
	this->LangEnButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnEnLangChanged);
	this->LangRuButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnRuLangChanged);
}

void UMSBJOptionsWidget::OnChangedMusicSlider(float Value)
{
	if (!this->MusicMenuClass)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("MusicClass is nullptr"));
		return;
	}
	this->MusicMenuClass->Properties.Volume = Value;
	int32 TempValue = Value * 100;
	this->MusicValueTextBlock->SetText(FText::FromString(FString::FromInt(TempValue)));
}

void UMSBJOptionsWidget::OnChangedSoundSlider(float Value)
{
	if (!this->SoundMenuClass)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("SoundClass is nullptr"));
		return;
	}
	this->SoundMenuClass->Properties.Volume = Value;
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

void UMSBJOptionsWidget::OnRuLangChanged()
{
	UKismetInternationalizationLibrary::SetCurrentCulture(FString("ru-RU"), false);
}

void UMSBJOptionsWidget::OnEnLangChanged()
{
	UKismetInternationalizationLibrary::SetCurrentCulture(FString("en"), false);
}
