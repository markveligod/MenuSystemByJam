/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "MSBJDataTypes.generated.h"

UENUM(BlueprintType)
enum class EMSBJGameMenuState : uint8
{
    InProgress = 0,
    Options,
    Credits
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuStateChangedSignature, EMSBJGameMenuState);

