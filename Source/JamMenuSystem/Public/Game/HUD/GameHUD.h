/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "Game/HUD/DebugHUD.h"
#include "GameHUD.generated.h"

class AGamePlayMode;
/**
 * @class Base game HUD
 */
UCLASS()
class JAMMENUSYSTEM_API AGameHUD : public ADebugHUD
{
	GENERATED_BODY()

protected:
    // Draw the HUD.
    virtual void DrawHUD() override;

    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    AGamePlayMode* GameMode;
};
