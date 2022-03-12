/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "HUD/UI/WelcomeUserWidget.h"

#include "JamMSGameMode.h"

void UWelcomeUserWidget::SetupStateWidget(const EStateObject NewState)
{
    Super::SetupStateWidget(NewState);
    if (NewState == EStateObject::Active)
    {
        GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::InProgress, GetStartAnim()->GetEndTime());
    }
}

void UWelcomeUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}
