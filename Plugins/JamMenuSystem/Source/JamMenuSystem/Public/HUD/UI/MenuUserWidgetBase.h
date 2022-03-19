/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#pragma once

#include "CoreMinimal.h"
#include "JamMSDataTypes.h"
#include "Blueprint/UserWidget.h"
#include "Library/JamMSFunctionLibrary.h"
#include "MenuUserWidgetBase.generated.h"

// Forward declare
class UJamMSGameInstance;
class AJamMSGameMode;

#define LOGMENU(verb, str) Print_Menu(verb, str, __LINE__, __FUNCTION__)

/**
 * @class Parent class for all widget menu system
 */
UCLASS()
class JAMMENUSYSTEM_API UMenuUserWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:

    // Log print from menu
    void Print_Menu(ELogVerb TypeVerb, FString Str, int Line, const char* Function) const;
    
#pragma region Action

    /**
     * @public Show animation
     * @param1 UWidgetAnimation
     **/
    UFUNCTION(BlueprintCallable, Category = "UMenuUserWidgetBase|Action")
    void ShowAnim(UWidgetAnimation* Anim);

    /**
     * @public Show animation for timer
     * @param1 UWidgetAnimation
     * @param2 float
     **/
    UFUNCTION(BlueprintCallable, Category = "UMenuUserWidgetBase|Action")
    void ShowAnimTimer(UWidgetAnimation* Anim, float RateTime);

    /**
     * @public Setup new state widget (Intended for override)
     * @param1 EStateObject
     **/
    virtual void SetupStateWidget(const EStateObject NewState);

#pragma endregion

#pragma region GetData

    /**
     * @public Getting Start animation
     * @return UWidgetAnimation
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE UWidgetAnimation* GetStartAnim() const { return this->StartAnim; }

    /**
     * @public Getting End animation
     * @return UWidgetAnimation
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE UWidgetAnimation* GetEndAnim() const { return this->EndAnim; }

    /**
     * @public Getting Current pointer on AJamMSGameMode class
     * @return AJamMSGameMode
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE AJamMSGameMode* GetGameMode() const { return this->GameMode; }

    /**
     * @public Getting Current pointer on UJamMSGameInstance class
     * @return UJamMSGameInstance
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE UJamMSGameInstance* GetGameInst() const { return this->GameInst; }

    /**
     * @public Getting current state widget
     * @return EStateObject
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE EStateObject GetStateWidget() const { return this->StateWidget; }

    /**
     * @public Getting current state button
     * @return EStateObject
     **/
    UFUNCTION(BlueprintPure, Category = "UMenuUserWidgetBase|GetData")
    FORCEINLINE EStateObject GetStateButton() const { return this->StateButton; }

#pragma endregion

protected:
    // Native handling for SObjectWidget
    virtual void NativeOnInitialized() override;

    /**
     * @public Show animation for timer
     * @param1 UWidgetAnimation
     * @param2 float
     **/
    UFUNCTION(BlueprintCallable, Category = "UMenuUserWidgetBase|Action")
    void SetupStateButton(EStateObject NewState);

    /**
     * @public Show animation for timer
     * @param1 UWidgetAnimation
     * @param2 float
     **/
    UFUNCTION(BlueprintCallable, Category = "UMenuUserWidgetBase|Action")
    void SetupStateButtonTimer(EStateObject NewState, float RateTime);

private:
    // @private Current pointer on AJamMSGameMode class
    UPROPERTY()
    AJamMSGameMode* GameMode;

    // @private Current pointer on UJamMSGameInstance class
    UPROPERTY()
    UJamMSGameInstance* GameInst;
    
    // @private State widget
    EStateObject StateWidget = EStateObject::Inactive;

    // @private State Button
    EStateObject StateButton = EStateObject::Inactive;

    // @private Animation at the start of visibility
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* StartAnim;

    // @private Animation at the end of visibility
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* EndAnim;

    // @private Timer Handle for show animation
    FTimerHandle TimerHandleShowAnim;

    // @private Timer Handle for show animation
    FTimerHandle TimerHandleButton;
};
