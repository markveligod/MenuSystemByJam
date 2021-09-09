/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/HUD/UI/MSBJCreditsWidget.h"
#include "Components/Button.h"
#include "Menu/MenuSystemByJamGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJCreditsWidget, All, All);

void UMSBJCreditsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (!this->BackButton)
    {
        UE_LOG(LogMSBJCreditsWidget, Error, TEXT("Lol NativeOnInitialized is nullptr"));
        return;
    }
    this->BackButton->OnClicked.AddDynamic(this, &UMSBJCreditsWidget::OnComeBack);
}

void UMSBJCreditsWidget::OnComeBack()
{
    const auto GameMode = GetCurrentGameMode();
    if (!GameMode)
    {
        UE_LOG(LogMSBJCreditsWidget, Error, TEXT("Game mode is nullptr"));
        return;
    }
    GameMode->SetGameState(EMSBJGameMenuState::InProgress);
}
