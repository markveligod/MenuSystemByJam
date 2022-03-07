/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "JamMSGameMode.h"
#include "JamMSGameInstance.h"
#include "MenuPlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "HUD/AMenuHUD.h"
#include "Library/JamMSFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogJamMSGameMode, All, All);

AJamMSGameMode::AJamMSGameMode()
{
    HUDClass = AMenuHUD::StaticClass();
    PlayerControllerClass = AMenuPlayerController::StaticClass();
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

    this->GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(this->GameInst != nullptr, "Game instance is nullptr")) return;
    
    this->UserSettings = UGameUserSettings::GetGameUserSettings();
    if (!CHECK(this->UserSettings != nullptr, "User settings is nullptr")) return;

    
}


