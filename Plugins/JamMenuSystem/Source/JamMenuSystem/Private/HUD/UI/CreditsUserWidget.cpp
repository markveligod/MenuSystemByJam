// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/CreditsUserWidget.h"

void UCreditsUserWidget::SetupStateWidget(const EStateObject NewState)
{
    Super::SetupStateWidget(NewState);
    if (NewState == EStateObject::Active)
    {
        PlayAnimation(this->LoopAnim, 0, 0);
    }
    else if (NewState == EStateObject::Inactive)
    {
        StopAnimation(this->LoopAnim);
    }
}

void UCreditsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}
