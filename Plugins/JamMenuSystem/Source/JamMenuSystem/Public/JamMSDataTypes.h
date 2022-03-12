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
    InProgress,
    Options,
    Credits
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
