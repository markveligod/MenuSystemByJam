/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/UI/MenuUserWidgetBase.h"
#include "JamMSGameInstance.h"
#include "Menu/JamMSGameMode.h"
#include "Library/JamMSFunctionLibrary.h"

void UMenuUserWidgetBase::Print_Menu(ELogVerb TypeVerb, FString Str, int Line, const char* Function) const
{
    UJamMSFunctionLibrary::Print_Log(TypeVerb, FString::Printf(TEXT("Name widget: %s | "), *GetName()) + Str, Line, Function);
}

void UMenuUserWidgetBase::ShowAnim(UWidgetAnimation* Anim)
{
    SetupStateButton(EStateObject::Inactive);
    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("Show animation: %s"), *Anim->GetName()));
    PlayAnimation(Anim);

    if (this->StateWidget == EStateObject::Active)
    {
        // Reset to active button
        FTimerHandle TimerHandle;
        FTimerDelegate TimerDelegate;
        TimerDelegate.BindLambda([this]
        {
            SetupStateButton(EStateObject::Active);
        });
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Anim->GetEndTime(), false);
        
        LOGMENU(ELogVerb::Display, FString::Printf(TEXT("Restart button state via: %f"), Anim->GetEndTime()));
    }
}

void UMenuUserWidgetBase::ShowAnimTimer(UWidgetAnimation* Anim, float RateTime)
{
    if (GetWorld()->GetTimerManager().TimerExists(this->TimerHandleShowAnim))
    {
        LOGMENU(ELogVerb::Warning, FString::Printf(TEXT("Timer Handle: %s is exist"), *this->TimerHandleShowAnim.ToString()));
        return;
    }

    if (RateTime <= 0.0f)
    {
        LOGMENU(ELogVerb::Warning, FString::Printf(TEXT("Call function with rate timer: %f <= 0.0"), RateTime));
        return;
    }
    
    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &UMenuUserWidgetBase::ShowAnim, Anim);
    GetWorld()->GetTimerManager().SetTimer(this->TimerHandleShowAnim, TimerDelegate, RateTime, false);

    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("Show Animation: %s via: %f"), *Anim->GetName(), Anim->GetEndTime()));
}

void UMenuUserWidgetBase::SetupStateButton(EStateObject NewState)
{
    if (this->StateWidget == EStateObject::Inactive) return;
    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("New State button: %s"), *UEnum::GetValueAsString(NewState)));
    this->StateButton = NewState;
}

void UMenuUserWidgetBase::SetupStateButtonTimer(EStateObject NewState, float RateTime)
{
    if (GetWorld()->GetTimerManager().TimerExists(this->TimerHandleButton))
    {
        LOGMENU(ELogVerb::Warning, FString::Printf(TEXT("Timer Handle: %s is exist"), *this->TimerHandleButton.ToString()));
        return;
    }

    if (RateTime <= 0.0f)
    {
        LOGMENU(ELogVerb::Warning, FString::Printf(TEXT("Call function with rate timer: %f <= 0.0"), RateTime));
        return;
    }

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindUObject(this, &UMenuUserWidgetBase::SetupStateButton, NewState);
    GetWorld()->GetTimerManager().SetTimer(this->TimerHandleShowAnim, TimerDelegate, RateTime, false);
}

void UMenuUserWidgetBase::SetupStateWidget(const EStateObject NewState)
{
    LOGMENU(ELogVerb::Display, FString::Printf(TEXT("New State widget: %s"), *UEnum::GetValueAsString(NewState)));
    this->StateWidget = NewState;
    SetupStateButton(NewState);
}

void UMenuUserWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    LOGMENU(ELogVerb::Display, "Native On Initialized");
    
    this->GameMode = AJamMSGameMode::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, "Game mode is nullptr")) return;

    this->GameInst = UJamMSGameInstance::Get(GetWorld());
    if (!CHECK(this->GameInst != nullptr, "Game instance is nullptr")) return;
    
}
