// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/HUD/UI/MSBJWelcomeWidget.h"
#include "Menu/MenuSystemByJamGameModeBase.h"

void UMSBJWelcomeWidget::NativeOnInitialized()
{
    check(GetWorld());
    GetWorld()->GetTimerManager().SetTimer(
        this->TimerWelcomeHandle, this, &UMSBJWelcomeWidget::ResetDelayAnimation, this->DelayTimer, false);
    this->GameMode = Cast<AMenuSystemByJamGameModeBase>(GetWorld()->GetAuthGameMode());
    check(this->GameMode);
}

void UMSBJWelcomeWidget::ResetDelayAnimation()
{
    GetWorld()->GetTimerManager().ClearTimer(this->TimerWelcomeHandle);
    this->GameMode->SetGameState(EMSBJGameMenuState::InProgress);
}
