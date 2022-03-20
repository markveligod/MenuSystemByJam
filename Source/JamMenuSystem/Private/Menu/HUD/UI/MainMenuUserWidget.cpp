/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#include "Menu/HUD/UI/MainMenuUserWidget.h"
#include "Menu/JamMSGameMode.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    this->NewGameButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::NewGame);
    this->SettingsButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::SwitchToSettings);
    this->CreditsButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::SwitchToCredits);
    this->ExitButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::CloseGame);
}

void UMainMenuUserWidget::NewGame()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(this->NewGameButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Loading, this->NewGameButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::SwitchToSettings()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(this->SettingsButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Settings, this->SettingsButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::SwitchToCredits()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(this->CreditsButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Credits, this->CreditsButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::CloseGame()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    LOGMENU(ELogVerb::Display, "Goodbye!");
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
