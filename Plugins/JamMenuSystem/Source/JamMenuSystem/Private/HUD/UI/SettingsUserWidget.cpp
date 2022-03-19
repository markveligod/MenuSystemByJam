/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "HUD/UI/SettingsUserWidget.h"
#include "JamMSGameMode.h"
#include "Components/Button.h"

void USettingsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    this->BackButton->OnClicked.AddDynamic(this, &USettingsUserWidget::ChangeToMainMenu);
}

void USettingsUserWidget::ChangeToMainMenu()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(BackButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::MainMenu, BackButtonAnim->GetEndTime());
}
