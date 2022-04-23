/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/UI/LoadingUserWidget.h"
#include "JamMSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULoadingUserWidget::SetupStateWidget(const EStateObject NewState)
{
    Super::SetupStateWidget(NewState);
    if (NewState == EStateObject::Active)
    {
        UGameplayStatics::OpenLevel(GetWorld(), GetGameInst()->GetNameStartLevel());
    }
}

void ULoadingUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}
