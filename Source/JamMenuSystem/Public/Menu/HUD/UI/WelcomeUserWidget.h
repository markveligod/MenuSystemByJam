/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MenuUserWidgetBase.h"
#include "WelcomeUserWidget.generated.h"

// Forward declare
class UImage;

/**
 * @class The usual widget for introductory pictures
 */
UCLASS()
class JAMMENUSYSTEM_API UWelcomeUserWidget : public UMenuUserWidgetBase
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
    // A picture that will act as a greeting
    UPROPERTY(Transient, meta = (BindWidget))
    UImage* WelcomeImage;
};
