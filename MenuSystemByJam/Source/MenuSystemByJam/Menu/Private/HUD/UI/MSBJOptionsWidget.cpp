/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "HUD/UI/MSBJOptionsWidget.h"

#include "MSBJGameInstance.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJOptionsWidget, All, All);

void UMSBJOptionsWidget::SetNewScreenSize(FString NewSize)
{
	int32 TempX = FCString::Atoi(*NewSize);
	int32 TempIndex;
	if (!NewSize.FindChar('x', TempIndex))
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("x char is not found"));
	int32 TempY = FCString::Atoi(&NewSize[TempIndex + 1]);
	UE_LOG(LogMSBJOptionsWidget, Display, TEXT("X: %d = Y: %d"), TempX, TempY);
	
	this->UserSettings->SetScreenResolution(FIntPoint(TempX, TempY));
	this->UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::SetQualityGame(int32 NumQuality)
{
	this->UserSettings->SetTextureQuality(NumQuality);
	this->UserSettings->SetAntiAliasingQuality(NumQuality);
	this->UserSettings->SetFoliageQuality(NumQuality);
	this->UserSettings->SetPostProcessingQuality(NumQuality);
	this->UserSettings->SetShadingQuality(NumQuality);
	this->UserSettings->SetShadowQuality(NumQuality);
	this->UserSettings->SetViewDistanceQuality(NumQuality);
	this->UserSettings->SetVisualEffectQuality(NumQuality);
	
	this->UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::NativeOnInitialized()
{
	check(GetWorld());
	
	this->GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	this->UserSettings = UGameUserSettings::GetGameUserSettings();
	
	checkf(this->GameInst, TEXT("Game Instance is nullptr"));
	checkf(this->UserSettings, TEXT("User settings is nullptr"));

	this->MusicSlider->SetMinValue(0.f);
	this->MusicSlider->SetMaxValue(100.f);
	this->SoundSlider->SetMinValue(0.f);
	this->SoundSlider->SetMaxValue(100.f);
	
	this->MusicMenuClass->Properties.Volume = float(this->GameInst->GetMusicVolumeValue() / 100.f);
	this->MusicValueTextBlock->SetText(this->GameInst->GetMusicVolumeText());

	this->SoundMenuClass->Properties.Volume = float(this->GameInst->GetSoundVolumeValue() / 100.f);
	this->SoundValueTextBlock->SetText(this->GameInst->GetSoundVolumeText());

	this->MusicSlider->SetValue(this->GameInst->GetMusicVolumeValue());
	this->SoundSlider->SetValue(this->GameInst->GetSoundVolumeValue());
	
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
	this->MusicMenuClass->Properties.Volume = float(Value / 100.f);
	this->MusicValueTextBlock->SetText(FText::FromString(FString::FromInt(int32(Value))));
}

void UMSBJOptionsWidget::OnChangedSoundSlider(float Value)
{
	if (!this->SoundMenuClass)
	{
		UE_LOG(LogMSBJOptionsWidget, Error, TEXT("SoundClass is nullptr"));
		return;
	}
	this->SoundMenuClass->Properties.Volume = float(Value / 100.f);
	this->SoundValueTextBlock->SetText(FText::FromString(FString::FromInt(int32(Value))));
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
	UE_LOG(LogMSBJOptionsWidget, Display, TEXT("Full Screen: %d"), bIsChecked);
	this->UserSettings->SetFullscreenMode(bIsChecked == true ? EWindowMode::Fullscreen : EWindowMode::Windowed);
	this->UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::OnRuLangChanged()
{
	UKismetInternationalizationLibrary::SetCurrentCulture(FString("ru-RU"), false);
}

void UMSBJOptionsWidget::OnEnLangChanged()
{
	UKismetInternationalizationLibrary::SetCurrentCulture(FString("en"), false);
}
