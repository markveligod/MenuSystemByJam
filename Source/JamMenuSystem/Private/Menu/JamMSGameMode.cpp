/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/JamMSGameMode.h"
#include "JamMSGameInstance.h"
#include "Menu/MenuPlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "Menu/HUD/AMenuHUD.h"
#include "Library/JamMSFunctionLibrary.h"

AJamMSGameMode::AJamMSGameMode()
{
    LOGJAM(ELogVerb::Display, "Game mode contructor");
    HUDClass = AMenuHUD::StaticClass();
    PlayerControllerClass = AMenuPlayerController::StaticClass();
}

void AJamMSGameMode::BeginPlay()
{
    Super::BeginPlay();

    this->GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(this->GameInst != nullptr, "Game instance is nullptr")) return;
    
    this->UserSettings = UGameUserSettings::GetGameUserSettings();
    if (!CHECK(this->UserSettings != nullptr, "User settings is nullptr")) return;

    ChangeMenuStateTimer(EJamMSMenuState::WelcomeToGame, 0.1f);
}

void AJamMSGameMode::ChangeMenuState(EJamMSMenuState NewState)
{
    if (this->MenuState == NewState)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Current menu state equal new state: %s"),
            *UEnum::GetValueAsString(NewState)));
        return;
    }

    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("New menu state: %s"), *UEnum::GetValueAsString(NewState)));
    this->MenuState = NewState;
    this->OnMenuStateChanged.Broadcast(NewState);
}

void AJamMSGameMode::ChangeMenuStateTimer(EJamMSMenuState NewState, float RateTime)
{
    if (RateTime <= 0.0f)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Call function with rate timer: %f <= 0.0"), RateTime));
        return;
    }
    
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &AJamMSGameMode::ChangeMenuState, NewState);
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, RateTime, false);
}

#pragma region ExecCheatFunc
void AJamMSGameMode::ChangeStateShowLog(const EStateShowLog NewState)
{
    StateShowLog = NewState;
}

#pragma endregion
