/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/HUD/UI/MSBJOptionsWidget.h"
#include "Menu/MSBJGameInstance.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJOptionsWidget, All, All);

void UMSBJOptionsWidget::NativeOnInitialized()
{
    check(GetWorld());

    this->GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
    this->UserSettings = UGameUserSettings::GetGameUserSettings();
    this->GameMode = GetCurrentGameMode();

    checkf(this->GameInst, TEXT("Game Instance is nullptr"));
    checkf(this->UserSettings, TEXT("User settings is nullptr"));
    checkf(this->GameMode, TEXT("Game mode is nullptr"));

    // delegate join
    this->MusicSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedMusicSlider);
    this->SoundSlider->OnValueChanged.AddDynamic(this, &UMSBJOptionsWidget::OnChangedSoundSlider);
    this->BackButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnComeBack);
    this->FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UMSBJOptionsWidget::OnFullScreenCheck);
    this->LangEnButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnEnLangChanged);
    this->LangRuButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnRuLangChanged);
    this->ScreenArrowLeftButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnClickScreenArrowLeft);
    this->ScreenArrowRightButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnClickScreenArrowRight);
    this->QualityArrowLeftButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnClickQualityArrowLeft);
    this->QualityArrowRightButton->OnClicked.AddDynamic(this, &UMSBJOptionsWidget::OnClickQualityArrowRight);
    this->GameMode->OnStartPlaySettings.AddUObject(this, &UMSBJOptionsWidget::SetupStartSettings);
}

void UMSBJOptionsWidget::OnChangedMusicSlider(float Value)
{
    this->GameInst->MusicMenuClass->Properties.Volume = float(Value / 100.f);
    this->MusicValueTextBlock->SetText(FText::FromString(FString::FromInt(int32(Value))));
}

void UMSBJOptionsWidget::OnChangedSoundSlider(float Value)
{
    this->GameInst->SoundMenuClass->Properties.Volume = float(Value / 100.f);
    this->SoundValueTextBlock->SetText(FText::FromString(FString::FromInt(int32(Value))));
}

void UMSBJOptionsWidget::OnComeBack()
{
    this->GameMode->SetGameState(EMSBJGameMenuState::InProgress);
}

void UMSBJOptionsWidget::OnFullScreenCheck(bool bIsChecked)
{
    UE_LOG(LogMSBJOptionsWidget, Display, TEXT("Full Screen: %d"), bIsChecked);
    if (bIsChecked == true)
    {
        this->UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
        this->GameInst->ChangeArrayScreenSize(true);
    }
    else
    {
        this->UserSettings->SetFullscreenMode(EWindowMode::Windowed);
        this->GameInst->ChangeArrayScreenSize(false);
    }
    const auto ResScreen = this->GameInst->GetScreenViewport();
    this->UserSettings->SetScreenResolution(ResScreen);
    this->ScreenModeTextBlock->SetText(FText::FromString(FString::FromInt(ResScreen.X) + "x" + FString::FromInt(ResScreen.Y)));
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

void UMSBJOptionsWidget::OnClickScreenArrowLeft()
{
    const auto ResScreen = this->GameInst->FindScreenSizeToLeftOnRight(true);
    this->UserSettings->SetScreenResolution(ResScreen);
    this->ScreenModeTextBlock->SetText(FText::FromString(FString::FromInt(ResScreen.X) + "x" + FString::FromInt(ResScreen.Y)));
    this->UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::OnClickScreenArrowRight()
{
    const auto ResScreen = this->GameInst->FindScreenSizeToLeftOnRight(false);
    this->UserSettings->SetScreenResolution(ResScreen);
    this->ScreenModeTextBlock->SetText(FText::FromString(FString::FromInt(ResScreen.X) + "x" + FString::FromInt(ResScreen.Y)));
    this->UserSettings->ApplySettings(false);
}

void UMSBJOptionsWidget::OnClickQualityArrowLeft()
{
    const auto TempIndexQuality = this->GameInst->ChangeQualityToLeftOnRight(true);
    this->ChangeQualitySettings(TempIndexQuality);
}

void UMSBJOptionsWidget::OnClickQualityArrowRight()
{
    const auto TempIndexQuality = this->GameInst->ChangeQualityToLeftOnRight(false);
    this->ChangeQualitySettings(TempIndexQuality);
}

void UMSBJOptionsWidget::ChangeQualitySettings(int32 Index)
{
    this->UserSettings->SetAntiAliasingQuality(Index);
    this->UserSettings->SetAudioQualityLevel(Index);
    this->UserSettings->SetFoliageQuality(Index);
    this->UserSettings->SetPostProcessingQuality(Index);
    this->UserSettings->SetShadingQuality(Index);
    this->UserSettings->SetShadowQuality(Index);
    this->UserSettings->SetTextureQuality(Index);
    this->UserSettings->SetViewDistanceQuality(Index);
    this->UserSettings->SetVisualEffectQuality(Index);
    this->UserSettings->ApplySettings(false);
    this->QualityModeTextBlock->SetText(this->ArrayQualityText[Index]);
}

void UMSBJOptionsWidget::SetupStartSettings()
{
    // FullScreen
    this->FullScreenCheckBox->SetCheckedState(
        (this->GameInst->GetCurrentWindowMode() == EWindowMode::Type::Fullscreen) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);

    // Music and sound part
    this->MusicSlider->SetMinValue(0.f);
    this->MusicSlider->SetMaxValue(100.f);
    this->SoundSlider->SetMinValue(0.f);
    this->SoundSlider->SetMaxValue(100.f);

    this->MusicSlider->SetValue(this->GameInst->GetMusicVolumeValue());
    this->SoundSlider->SetValue(this->GameInst->GetSoundVolumeValue());

    this->GameInst->MusicMenuClass->Properties.Volume = float(this->GameInst->GetMusicVolumeValue() / 100.f);
    this->MusicValueTextBlock->SetText(this->GameInst->GetMusicVolumeText());

    this->GameInst->SoundMenuClass->Properties.Volume = float(this->GameInst->GetSoundVolumeValue() / 100.f);
    this->SoundValueTextBlock->SetText(this->GameInst->GetSoundVolumeText());

    // Screen Size
    const auto TempScreen = this->GameInst->GetScreenViewport();
    this->ScreenModeTextBlock->SetText(FText::FromString(FString::FromInt(TempScreen.X) + "x" + FString::FromInt(TempScreen.Y)));

    // Quality
    this->ArrayQualityText.Add(FText::FromString("Low"));
    this->ArrayQualityText.Add(FText::FromString("Medium"));
    this->ArrayQualityText.Add(FText::FromString("High"));
    this->ArrayQualityText.Add(FText::FromString("Epic"));
    this->ArrayQualityText.Add(FText::FromString("Cinematic"));

    this->QualityModeTextBlock->SetText(this->ArrayQualityText[this->GameInst->GetCurrentQualityValue()]);
}
