/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MenuUserWidgetBase.h"
#include "CreditsUserWidget.generated.h"

// Forward declare
class UButton;

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

    // @private Button close to Main menu
    UPROPERTY(Transient, meta = (BindWidget))
    UButton* BackButton;
    // @private Button close to Main menu Animation
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* BackButtonAnim;

    /**
     * @private To return to the main menu
     **/
    UFUNCTION()
    void ChangeToMainMenu();
};
