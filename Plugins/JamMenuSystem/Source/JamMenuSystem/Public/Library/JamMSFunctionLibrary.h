/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JamMSFunctionLibrary.generated.h"

UENUM(Blueprintable)
enum class ELogVerb: uint8
{
    Display,
    Warning,
    Error
};

DEFINE_LOG_CATEGORY_STATIC(LogJamMenuSystem, All, All);

#define CHECK(exp, str) UJamMSFunctionLibrary::Print_Exp(exp, str, __LINE__, __FUNCTION__)
#define LOGJAM(verb, str) UJamMSFunctionLibrary::Print_Log(verb, str, __LINE__, __FUNCTION__)

/**
 * @class Functional library for project support
 */
UCLASS()
class JAMMENUSYSTEM_API UJamMSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    
    // Checking expressions for print log
    static bool Print_Exp(bool Var, FString Str, int Line, const char* Function);
    
    // Print a log on screen(UE_EDITOR only) and in ULOG
    static void Print_Log(ELogVerb TypeVerb, FString Str, int Line, const char* Function);
};
