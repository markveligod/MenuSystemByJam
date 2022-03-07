/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "HUD/UI/MenuUserWidgetBase.h"
#include "JamMSGameInstance.h"
#include "JamMSGameMode.h"
#include "Library/JamMSFunctionLibrary.h"

void UMenuUserWidgetBase::ShowAnim(UWidgetAnimation* Anim)
{
    PlayAnimation(Anim);
}

void UMenuUserWidgetBase::ShowAnimTimer(UWidgetAnimation* Anim, float RateTime)
{
    if (GetWorld()->GetTimerManager().TimerExists(this->TimerHandleShowAnim))
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Timer Handle: %s is exist"), *this->TimerHandleShowAnim.ToString()));
        return;
    }

    if (RateTime <= 0.0f)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Call function with rate timer: %f <= 0.0"), RateTime));
        return;
    }

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUFunction(this, "UMenuUserWidgetBase::ShowAnim", Anim);
    GetWorld()->GetTimerManager().SetTimer(this->TimerHandleShowAnim, TimerDelegate, RateTime, false);
}

void UMenuUserWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    this->GameMode = AJamMSGameMode::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, "Game mode is nullptr")) return;

    this->GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(this->GameInst != nullptr, "Game instance is nullptr")) return;
    
}
