// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Menu/MSBJDataTypes.h"
#include "GameJamModeBase.generated.h"

/**
 *
 */
UCLASS()
class MENUSYSTEMBYJAM_API AGameJamModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    AGameJamModeBase();

    void ChangeGameState(EGameLevelState NewState);

    FOnGameLevelStateChangedSignature OnGameLevelStateChanged;

protected:
    virtual void StartPlay() override;

private:
    class UMSBJGameInstance* GameInst;
    class UGameUserSettings* UserSettings;
    EGameLevelState CurrentGameState = EGameLevelState::WaitToStart;

    void SetupStartLevelSettings();
};
