/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/UI/SettingsUserWidget.h"
#include "JamMSGameInstance.h"
#include "Menu/JamMSGameMode.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"

void USettingsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    this->BackButton->OnClicked.AddDynamic(this, &USettingsUserWidget::ChangeToMainMenu);
   
    this->MusicCheckBox->CheckedState = GetGameInst()->GetMusicMenuClass()->Properties.Volume == 0.0f ? ECheckBoxState::Unchecked : ECheckBoxState::Checked;
    this->SoundCheckBox->CheckedState = GetGameInst()->GetSoundMenuClass()->Properties.Volume == 0.0f ? ECheckBoxState::Unchecked : ECheckBoxState::Checked;
    
    this->MusicCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsUserWidget::ChangeMusicVolume);
    this->SoundCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsUserWidget::ChangeSoundVolume);

    this->ResolutionComboBoxString->ClearOptions();
    TArray<FIntPoint> ArraySizePoint = GetGameInst()->GetArrayWindowedScreenSize();
    for (const auto Point : ArraySizePoint)
    {
        this->ResolutionComboBoxString->AddOption(FString::FromInt(Point.X) + "x" + FString::FromInt(Point.Y));
    }
    this->ResolutionComboBoxString->SetSelectedOption(UJamMSFunctionLibrary::GetStringSizeScreen(GetGameInst()->GetSelectedScreenSize()));
}

void USettingsUserWidget::ChangeToMainMenu()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(BackButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::MainMenu, BackButtonAnim->GetEndTime());
}

void USettingsUserWidget::ChangeMusicVolume(bool bIsChecked)
{
    const float NewVolumeValue = bIsChecked ? GetGameInst()->GetDefaultMusicVolumeValue() / VALUE_PERCENT : 0.0f;
    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("Name checkbox: %s | State: %s | Current Music volume: %f | New Music volume: %f"),
        *this->MusicCheckBox->GetName(), *UJamMSFunctionLibrary::GetStringFromBool(bIsChecked),
        GetGameInst()->GetMusicMenuClass()->Properties.Volume, NewVolumeValue));
    
    GetGameInst()->GetMusicMenuClass()->Properties.Volume = NewVolumeValue;
}

void USettingsUserWidget::ChangeSoundVolume(bool bIsChecked)
{
    const float NewVolumeValue = bIsChecked ? GetGameInst()->GetDefaultSoundVolumeValue() / VALUE_PERCENT : 0.0f;
    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("Name checkbox: %s | State: %s | Current Sound volume: %f | New Sound volume: %f"),
        *this->MusicCheckBox->GetName(), *UJamMSFunctionLibrary::GetStringFromBool(bIsChecked),
        GetGameInst()->GetSoundMenuClass()->Properties.Volume, NewVolumeValue));
    
    GetGameInst()->GetSoundMenuClass()->Properties.Volume = bIsChecked ? GetGameInst()->GetDefaultSoundVolumeValue() / VALUE_PERCENT : 0.0f;
}

