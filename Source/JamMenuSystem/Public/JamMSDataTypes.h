/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "JamMSDataTypes.generated.h"

/* Determines the current state of the menu */
UENUM(BlueprintType)
enum class EJamMSMenuState : uint8
{
    WaitToStart = 0,
    WelcomeToGame,
    MainMenu,
    Settings,
    Credits,
    Loading
};

/* Delegate for change the menu state */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMenuStateChangedSignature, EJamMSMenuState, MenuState);

// A common set of states for any objects
UENUM(BlueprintType)
enum class EStateObject: uint8
{
    Active,
    Inactive
};

/* Defines the status to display on the screen */
UENUM()
enum class EStateShowLog : uint8
{
    Error = 0,
    Warning,
    All
};
