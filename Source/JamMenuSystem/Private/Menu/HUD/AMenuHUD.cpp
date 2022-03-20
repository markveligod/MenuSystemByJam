/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Menu/HUD/AMenuHUD.h"
#include "Menu/JamMSGameMode.h"
#include "Library/JamMSFunctionLibrary.h"
#include "Menu/HUD/UI/MenuUserWidgetBase.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    this->GameMode = AJamMSGameMode::Get(GetWorld());
    if (!CHECK(this->GameMode != nullptr, "Game mode is nullptr")) return;

    if (!CHECK(this->WelcomeHudWidgetClass.GetDefaultObject() != nullptr, "WelcomeHudWidgetClass is nullptr")) return;
    if (!CHECK(this->MenuHudWidgetClass.GetDefaultObject() != nullptr, "MenuHudWidgetClass is nullptr")) return;
    if (!CHECK(this->SettingsHudWidgetClass.GetDefaultObject() != nullptr, "OptionsHudWidgetClass is nullptr")) return;
    if (!CHECK(this->CreditsHudWidgetClass.GetDefaultObject() != nullptr, "CreditsHudWidgetClass is nullptr")) return;

    this->MenuWidgets.Add(EJamMSMenuState::WelcomeToGame,
        CreateWidget<UMenuUserWidgetBase>(GetWorld(), this->WelcomeHudWidgetClass));
    this->MenuWidgets.Add(EJamMSMenuState::MainMenu,
        CreateWidget<UMenuUserWidgetBase>(GetWorld(), this->MenuHudWidgetClass));
    this->MenuWidgets.Add(EJamMSMenuState::Settings,
        CreateWidget<UMenuUserWidgetBase>(GetWorld(), this->SettingsHudWidgetClass));
    this->MenuWidgets.Add(EJamMSMenuState::Credits,
        CreateWidget<UMenuUserWidgetBase>(GetWorld(), this->CreditsHudWidgetClass));
    this->MenuWidgets.Add(EJamMSMenuState::Loading,
        CreateWidget<UMenuUserWidgetBase>(GetWorld(), this->LoadingHudWidgetClass));

    for (const auto Widget : this->MenuWidgets)
    {
        const auto ValueWidget = Widget.Value;
        ValueWidget->AddToViewport();
        ValueWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    
    this->GameMode->OnMenuStateChanged.AddDynamic(this, &AMenuHUD::OnMenuStateChanged);
}

void AMenuHUD::OnMenuStateChanged(EJamMSMenuState NewState)
{
    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("New State in HUD: %s"), *UEnum::GetValueAsString(NewState)));

    if (!CHECK(this->MenuWidgets.Contains(NewState), FString::Printf(TEXT("State: %s don't contains in TMap widgets"),
        *UEnum::GetValueAsString(NewState)))) return;
    
    if (this->MenuWidget)
    {
        FTimerHandle TimerHandle;
        FTimerDelegate TimerDelegate;
        this->MenuWidget->SetupStateWidget(EStateObject::Inactive);
        this->MenuWidget->ShowAnim(this->MenuWidget->GetEndAnim());

        TimerDelegate.BindUObject(this, &AMenuHUD::SwitchWidget, this->MenuWidget, this->MenuWidgets[NewState]);
        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, this->MenuWidget->GetEndAnim()->GetEndTime(), false);
    }
    else
    {
        this->SetupNewWidget(this->MenuWidgets[NewState]);
    }
}

void AMenuHUD::SetupNewWidget(UMenuUserWidgetBase* Widget)
{
    if (!CHECK(Widget != nullptr, "Widget is nullptr")) return;
    if (this->MenuWidget == Widget)
    {
        LOGJAM(ELogVerb::Warning, FString::Printf(TEXT("Menu widget equal pointer on new widget: %s"), *Widget->GetName()));
        return;
    }
    
    this->MenuWidget = Widget;
    this->MenuWidget->SetupStateWidget(EStateObject::Active);
    this->MenuWidget->SetVisibility(ESlateVisibility::Visible);
    this->MenuWidget->ShowAnim(this->MenuWidget->GetStartAnim());
}

void AMenuHUD::SwitchWidget(UMenuUserWidgetBase* OldWidget, UMenuUserWidgetBase* NewWidget)
{
    OldWidget->SetVisibility(ESlateVisibility::Hidden);
    this->MenuWidget = nullptr;
    this->SetupNewWidget(NewWidget);
}
