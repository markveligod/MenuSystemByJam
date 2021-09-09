/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/HUD/MSBJMenuHUD.h"
#include "Menu/HUD/UI/MSBJBaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/MenuSystemByJamGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJMenuHUD, All, All);

void AMSBJMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    check(GetWorld());

    this->GameWidgets.Add(EMSBJGameMenuState::WelcomeToGame, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->WelcomeHudWidgetClass));
    this->GameWidgets.Add(EMSBJGameMenuState::InProgress, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->MenuHudWidgetClass));
    this->GameWidgets.Add(EMSBJGameMenuState::Options, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->OptionsHudWidgetClass));
    this->GameWidgets.Add(EMSBJGameMenuState::Credits, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->CreditsHudWidgetClass));

    for (auto Widget : this->GameWidgets)
    {
        const auto ValueWidget = Widget.Value;
        ValueWidget->AddToViewport();
        ValueWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    const auto GameMode = Cast<AMenuSystemByJamGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
    {
        UE_LOG(LogMSBJMenuHUD, Error, TEXT("Game Mode is nullptr"));
        return;
    }
    GameMode->OnGameMenuStateChangedSignature.AddUObject(this, &AMSBJMenuHUD::OnGameStateChanged);
}

void AMSBJMenuHUD::OnGameStateChanged(EMSBJGameMenuState NewState)
{
    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (this->GameWidgets.Contains(NewState))
    {
        this->CurrentWidget = this->GameWidgets[NewState];
    }
    if (this->CurrentWidget)
    {
        this->CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        this->CurrentWidget->Show();
    }
    UE_LOG(LogMSBJMenuHUD, Display, TEXT("New State: %s"), *UEnum::GetValueAsString(NewState))
}
