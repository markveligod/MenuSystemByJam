// Copyright Epic Games, Inc. All Rights Reserved.

/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Menu/MSBJDataTypes.h"
#include "MenuSystemByJamGameModeBase.generated.h"

class UMSBJGameInstance;

/**
 *
 */
UCLASS()
class MENUSYSTEMBYJAM_API AMenuSystemByJamGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    FOnStartPlaySettingsSignature OnStartPlaySettings;
    FOnGameMenuStateChangedSignature OnGameMenuStateChangedSignature;

    AMenuSystemByJamGameModeBase();

    virtual void StartPlay() override;
    const EMSBJGameMenuState& GetCurrentState() const;
    void SetGameState(EMSBJGameMenuState NewState);

protected:
private:
    // Pointer Classes
    UMSBJGameInstance* GameInstance;
    UGameUserSettings* UserSettings;

    // Variables
    EMSBJGameMenuState CurrentState = EMSBJGameMenuState::WaitToStart;

    // Functions
    void StartPlayGameModeSettings();
};
