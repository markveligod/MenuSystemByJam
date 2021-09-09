/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSBJBaseWidget.generated.h"

class AMenuSystemByJamGameModeBase;

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* ShowAnimation;

	AMenuSystemByJamGameModeBase* GetCurrentGameMode() const;
};
