/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#include "HUD/UI/MainMenuUserWidget.h"
#include "JamMSGameMode.h"
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
    ShowAnim(this->NewGameButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Loading, this->NewGameButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::SwitchToSettings()
{
    ShowAnim(this->SettingsButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Options, this->SettingsButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::SwitchToCredits()
{
    ShowAnim(this->CreditsButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::Credits, this->CreditsButtonAnim->GetEndTime());
}

void UMainMenuUserWidget::CloseGame()
{
    LOGMENU(ELogVerb::Display, "Goodbye!");
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
