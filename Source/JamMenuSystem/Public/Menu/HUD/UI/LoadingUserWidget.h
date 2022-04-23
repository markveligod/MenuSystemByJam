/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/
#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MenuUserWidgetBase.h"
#include "LoadingUserWidget.generated.h"

/**
 * @class Plug for loading the level
 */
UCLASS()
class JAMMENUSYSTEM_API ULoadingUserWidget : public UMenuUserWidgetBase
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
    
};
