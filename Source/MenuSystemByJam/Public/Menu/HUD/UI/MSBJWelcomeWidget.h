// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MSBJBaseWidget.h"
#include "MSBJWelcomeWidget.generated.h"

class AMenuSystemByJamGameModeBase;

/**
 *
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJWelcomeWidget : public UMSBJBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer editor")
    float DelayTimer = 4.f;

    virtual void NativeOnInitialized() override;

private:
    FTimerHandle TimerWelcomeHandle;

    AMenuSystemByJamGameModeBase* GameMode;

    UFUNCTION()
    void ResetDelayAnimation();
};
