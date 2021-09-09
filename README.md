# :taurus: Menu System By Jam (Technical documentation)

## :wastebasket: How to use this nonsense ?
1. Download renom.exe from https://github.com/UnrealisticDev/Renom  
2. Run renom.exe  
3. Insert the path to the project  
4. Enter a new project name
5. Done!  

## :clipboard: Description
### :video_game: Game Mode and Game instance
Path Game mode: Source/MenuSystemByJam/public(private)/Menu/MenuSystemByJamGameModeBase.h(.cpp)  
Path Game instance: Source/MenuSystemByJam/public(private)/Menu/MSBJGameInstance.h(.cpp)  
The main task of the `AMenuSystemByJamGameModeBase` class is to switch states and notify with the help of a delegate `FOnGameMenuStateChangedSignature` about a change in the menu state.
```
/* Determines the current state of the menu */
UENUM(BlueprintType)
enum class EMSBJGameMenuState : uint8
{
    WaitToStart = 0,
    WelcomeToGame,
    InProgress,
    Options,
    Credits
};

/* Delegate for change the menu state*/
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuStateChangedSignature, EMSBJGameMenuState);
```
The next important component of the project is the launch of pre-start settings when calling the function `virtual void StartPlay() override;`  
The start settings are started by getting them from the class `UMSBJGameInstance`. The class `UMSBJGameInstance` is common to the entire project and lives throughout the entire launch of the game until its completion.  
The basic starting settings are carried out in the function `void StartPlayGameModeSettings();`
```
void AMenuSystemByJamGameModeBase::StartPlay()
{
    Super::StartPlay();
    this->UserSettings = UGameUserSettings::GetGameUserSettings();
    this->GameInstance = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());

    checkf(this->UserSettings, TEXT("User Settings is nullptr"));
    checkf(this->GameInstance, TEXT("Game instance is nullptr"));

    this->StartPlayGameModeSettings();
    this->SetGameState(EMSBJGameMenuState::WelcomeToGame);
}

...

void AMenuSystemByJamGameModeBase::StartPlayGameModeSettings()
{
    this->OnStartPlaySettings.Broadcast();
    UKismetInternationalizationLibrary::SetCurrentCulture(this->GameInstance->GetCurrentLanguage(), false);
    this->UserSettings->SetFullscreenMode(this->GameInstance->GetCurrentWindowMode());
    this->UserSettings->SetScreenResolution(this->GameInstance->GetScreenViewport());
    this->UserSettings->SetAntiAliasingQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetAudioQualityLevel(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetFoliageQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetPostProcessingQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetShadingQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetShadowQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetTextureQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetViewDistanceQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->SetVisualEffectQuality(this->GameInstance->GetCurrentQualityValue());
    this->UserSettings->ApplySettings(false);
}
```

### :calling: HUD and UI
Path HUD: Source/MenuSystemByJam/public(private)/Menu/HUD/MSBJMenuHUD.h(.cpp)
Path UI: Source/MenuSystemByJam/public(private)/Menu/HUD/UI/*

The `AMSBJMenuHUD` class contains a set of refs widgets that will be drawn on the player's screen:
```
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UMSBJBaseWidget> WelcomeHudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UMSBJBaseWidget> MenuHudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UMSBJBaseWidget> OptionsHudWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UMSBJBaseWidget> CreditsHudWidgetClass;
```
This `WelcomeHudWidgetClass` parameter is responsible for drawing the window welcome at the start of the game.  
This `MenuHudWidgetClass` parameter is responsible for drawing the main menu.  
This `OptionsHudWidgetClass` parameter is responsible for drawing the game settings.  
This `CreditsHudWidgetClass` parameter is responsible for drawing the authors of the game.  
  
All widgets are created in an `TMap<EMSBJGameMenuState, UMSBJBaseWidget*> GameWidgets;` in the function `virtual void BeginPlay() override;`  
```
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
```

Changing the widget just depends on the delegate `FOnGameMenuStateChangedSignature` that allows you to receive an alert about changing the status menu through the function `void OnGameStateChanged(EMSBJGameMenuState NewState);`.

```
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
```




## 📫 Other
:bangbang: Attention: If you can improve my trash code then make a pull request.  
:bangbang: Attention: If you still have questions, write to the section Issues.

**:copyright:Authors:**  
  
*[Mark Veligod](https://github.com/markveligod)*  
