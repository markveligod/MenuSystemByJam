/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/HUD/UI/MSBJMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "Menu/MSBJGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJMenuWidget, All, All);

void UMSBJMenuWidget::NativeOnInitialized()
{
    if (!this->StartGameButton || !this->OptionsButton || !this->CreditsButton || !this->QuitButton)
    {
        UE_LOG(LogMSBJMenuWidget, Error, TEXT("Button is nullptr"));
        return;
    }

    this->StartGameButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnStartGame);
    this->OptionsButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnOptionsGame);
    this->CreditsButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnCreditsGame);
    this->QuitButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnQuitGame);
}

void UMSBJMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;
    const auto GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
    PlayAnimation(this->EndAnimation);
    UGameplayStatics::OpenLevel(GetWorld(), GameInst->NameStartLevel);
}

void UMSBJMenuWidget::OnOptionsGame()
{
    const auto GameMode = GetCurrentGameMode();
    if (!GameMode)
    {
        UE_LOG(LogMSBJMenuWidget, Error, TEXT("Game mode is nullptr"));
        return;
    }
    GameMode->SetGameState(EMSBJGameMenuState::Options);
}

void UMSBJMenuWidget::OnCreditsGame()
{
    const auto GameMode = GetCurrentGameMode();
    if (!GameMode)
    {
        UE_LOG(LogMSBJMenuWidget, Error, TEXT("Game mode is nullptr"));
        return;
    }
    GameMode->SetGameState(EMSBJGameMenuState::Credits);
}

void UMSBJMenuWidget::OnQuitGame()
{
    PlayAnimation(this->EndAnimation);
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
    UE_LOG(LogMSBJMenuWidget, Display, TEXT("Goodbye!"));
}
