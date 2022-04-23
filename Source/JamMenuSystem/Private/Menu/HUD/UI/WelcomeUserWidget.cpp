/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/UI/WelcomeUserWidget.h"
#include "Menu/JamMSGameMode.h"

void UWelcomeUserWidget::SetupStateWidget(const EStateObject NewState)
{
    Super::SetupStateWidget(NewState);
    if (NewState == EStateObject::Active)
    {
        GetGameMode()->ChangeMenuStateTimer(EJamMSMenuState::MainMenu, GetStartAnim()->GetEndTime());
    }
}

void UWelcomeUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}
