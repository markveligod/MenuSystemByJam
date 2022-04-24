/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamePlayMode.generated.h"

/**
 * @class 
 */
UCLASS()
class JAMMENUSYSTEM_API AGamePlayMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    // Get singleton class
    static AGamePlayMode* Get(UWorld* World) { return (World) ? Cast<AGamePlayMode>(World->GetAuthGameMode()) : nullptr; }
};
