/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/HUD/UI/MSBJBaseWidget.h"
#include "Menu/MenuSystemByJamGameModeBase.h"

void UMSBJBaseWidget::Show()
{
    PlayAnimation(this->ShowAnimation);
}

AMenuSystemByJamGameModeBase* UMSBJBaseWidget::GetCurrentGameMode() const
{
    return (GetWorld() ? Cast<AMenuSystemByJamGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr);
}
