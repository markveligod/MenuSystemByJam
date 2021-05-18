/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "MSBJDataTypes.generated.h"

/* Determines the current state of the menu */
UENUM(BlueprintType)
enum class EMSBJGameMenuState : uint8
{
	WaitToStart = 0,
	WelcomeToGame,
    InProgress,
    Options,
    Credits
};

/* Delegate for change the menu state*/
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuStateChangedSignature, EMSBJGameMenuState);
DECLARE_MULTICAST_DELEGATE(FOnStartPlaySettingsSignature);

/* Determines the current state of the game */
UENUM(BlueprintType)
enum class EGameLevelState : uint8
{
    WaitToStart = 0,
    InProgress,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameLevelStateChangedSignature, EGameLevelState);


