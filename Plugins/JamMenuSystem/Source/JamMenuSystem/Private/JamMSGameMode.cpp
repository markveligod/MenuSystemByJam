/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://veligodstudio.itch.io/
 **/

#include "JamMSGameMode.h"

#include "JamMSGameInstance.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogJamMSGameMode, All, All);

AJamMSGameMode::AJamMSGameMode()
{
}

void AJamMSGameMode::ChangeMenuState(EJamMSMenuState NewState)
{
    if (this->MenuState == NewState)
    {
        UE_LOG(LogJamMSGameMode, Warning, TEXT("Current menu state equal new state: %s"),
            *UEnum::GetValueAsString(NewState));
        return;
    }

    this->MenuState = NewState;
    this->OnMenuStateChanged.Broadcast(NewState);
}

void AJamMSGameMode::BeginPlay()
{
    Super::BeginPlay();

    this->GameInstance = Cast<UJamMSGameInstance>(GetWorld()->GetAuthGameMode());
    checkf(this->GameInstance, TEXT("Game instance is nullptr"));

    this->UserSettings = UGameUserSettings::GetGameUserSettings();
    checkf(this->UserSettings, TEXT("User settings is nullptr"));
}


