/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "JamMSDataTypes.h"
#include "GameFramework/HUD.h"
#include "AMenuHUD.generated.h"

// Forward declare
class UMenuUserWidgetBase;
class AJamMSGameMode;

/**
 * @class Menu HUD
 */
UCLASS()
class JAMMENUSYSTEM_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

    /**
     * @public Getting current pointer on AJamMSGameMode
     * @return AJamMSGameMode
     **/
    AJamMSGameMode* GetGameMode() const { return this->GameMode; }
    
protected:
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;
    
private:

    // @private Current pointer on AJamMSGameMode class
    UPROPERTY()
    AJamMSGameMode* GameMode;
    
    // @private Current sub class on UMenuUserWidgetBase from WelcomeHudWidgetClass
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuUserWidgetBase> WelcomeHudWidgetClass;

    // @private Current sub class on UMenuUserWidgetBase from MenuHudWidgetClass
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuUserWidgetBase> MenuHudWidgetClass;

    // @private Current sub class on UMenuUserWidgetBase from OptionsHudWidgetClass
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuUserWidgetBase> SettingsHudWidgetClass;

    // @private Current sub class on UMenuUserWidgetBase from CreditsHudWidgetClass
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuUserWidgetBase> CreditsHudWidgetClass;

    // @private Current sub class on UMenuUserWidgetBase from CreditsHudWidgetClass
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UMenuUserWidgetBase> LoadingHudWidgetClass;

    // @private Container for storing widgets
    UPROPERTY()
    TMap<EJamMSMenuState, UMenuUserWidgetBase*> MenuWidgets;

    // @private Current pointer on UMenuUserWidgetBase in visible on HUD
    UPROPERTY()
    UMenuUserWidgetBase* MenuWidget = nullptr;

    /**
     * @private Registers the new state of the system menu
     * @param1 EJamMSMenuState
     **/
    UFUNCTION()
    void OnMenuStateChanged(EJamMSMenuState NewState);

    /**
     * @private Setup new widget visible
     * @param1 UMenuUserWidgetBase
     **/
    UFUNCTION()
    void SetupNewWidget(UMenuUserWidgetBase* Widget);

    /**
     * @private Setup new widget visible
     * @param1 UMenuUserWidgetBase
     **/
    void SwitchWidget(UMenuUserWidgetBase* OldWidget, UMenuUserWidgetBase* NewWidget);
    
};

