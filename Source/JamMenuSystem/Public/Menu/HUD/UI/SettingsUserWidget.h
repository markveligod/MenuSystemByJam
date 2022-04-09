/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MenuUserWidgetBase.h"
#include "SettingsUserWidget.generated.h"

// Forward declare
class UButton;
class UComboBoxString;
class UCheckBox;

/**
 * @class For the widget menu by standard settings
 */
UCLASS()
class JAMMENUSYSTEM_API USettingsUserWidget : public UMenuUserWidgetBase
{
	GENERATED_BODY()

protected:
    // Native handling for SObjectWidget
    virtual void NativeOnInitialized() override;

private:
    // @private Switch for music
    UPROPERTY(Transient, meta = (BindWidget))
    UCheckBox* MusicCheckBox;
    
    // @private Switch for sound
    UPROPERTY(Transient, meta = (BindWidget))
    UCheckBox* SoundCheckBox;

    // @private list of available screen resolutions
    UPROPERTY(Transient, meta = (BindWidget))
    UComboBoxString* ResolutionComboBoxString;

    // @private list of available Language
    UPROPERTY(Transient, meta = (BindWidget))
    UComboBoxString* LanguageComboBoxString;

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

    /**
     * @private Change music volume class
     **/
    UFUNCTION()
    void ChangeMusicVolume(bool bIsChecked);

    /**
     * @private Change sound volume class
     **/
    UFUNCTION()
    void ChangeSoundVolume(bool bIsChecked);

    /**
     * @private Change sound volume class
     **/
    UFUNCTION()
    void ChangeSelectedScreenSize(FString SelectedItem, ESelectInfo::Type SelectionType);

    /**
     * @private Change language game
     **/
    UFUNCTION()
    void ChangeLangGame(FString SelectedItem, ESelectInfo::Type SelectionType);
};

