/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUserWidgetBase.generated.h"

// Forward declare
class UJamMSGameInstance;
class AJamMSGameMode;

/**
 * @class Parent class for all widget menu system
 */
UCLASS()
class JAMMENUSYSTEM_API UMenuUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
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

protected:
    // Native handling for SObjectWidget
    virtual void NativeOnInitialized() override;
    
private:

    // @private Current pointer on AJamMSGameMode class
    UPROPERTY()
    AJamMSGameMode* GameMode;

    // @private Current pointer on UJamMSGameInstance class
    UPROPERTY()
    UJamMSGameInstance* GameInst;
    
    // @private Animation at the start of visibility
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* StartAnim;

    // @private Animation at the end of visibility
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* EndAnim;

    // Timer Handle for show animation
    FTimerHandle TimerHandleShowAnim;
};
