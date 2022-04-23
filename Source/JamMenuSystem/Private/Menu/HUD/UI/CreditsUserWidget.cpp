/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/UI/CreditsUserWidget.h"
#include "Menu/JamMSGameMode.h"
#include "Components/Button.h"

void UCreditsUserWidget::SetupStateWidget(const EStateObject NewState)
{
    Super::SetupStateWidget(NewState);
    if (NewState == EStateObject::Active)
    {
        PlayAnimation(this->LoopAnim, 0, 0);
    }
    else if (NewState == EStateObject::Inactive)
    {
        StopAnimation(this->LoopAnim);
    }
}

void UCreditsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    this->BackButton->OnClicked.AddDynamic(this, &UCreditsUserWidget::ChangeToMainMenu);
}

void UCreditsUserWidget::ChangeToMainMenu()
{
    if (GetStateButton() == EStateObject::Inactive) return;
    ShowAnim(BackButtonAnim);
    GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::MainMenu, BackButtonAnim->GetEndTime());
}
