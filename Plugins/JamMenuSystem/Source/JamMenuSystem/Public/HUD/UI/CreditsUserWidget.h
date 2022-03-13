// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MenuUserWidgetBase.h"
#include "CreditsUserWidget.generated.h"

/**
 * @class Widget class for displaying creators
 */
UCLASS()
class JAMMENUSYSTEM_API UCreditsUserWidget : public UMenuUserWidgetBase
{
	GENERATED_BODY()

public:
    /**
     * @public Setup new state widget (Intended for override)
     * @param1 EStateObject
     **/
    virtual void SetupStateWidget(const EStateObject NewState) override;

protected:
    // Native handling for SObjectWidget
    virtual void NativeOnInitialized() override;

private:
    // Looping animation (ZALUPING :D)
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* LoopAnim;
};
