/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "Menu/HUD/UI/MSBJBaseWidget.h"
#include "MSBJOptionsWidget.generated.h"

class USlider;
class UTextBlock;
class UButton;
class UCheckBox;
class USoundClass;
class UMSBJGameInstance;
class UGameUserSettings;
class AMenuSystemByJamGameModeBase;

/**
 *
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJOptionsWidget : public UMSBJBaseWidget
{
    GENERATED_BODY()

public:
protected:
    UPROPERTY(meta = (BindWidget))
    USlider* MusicSlider;
    UPROPERTY(meta = (BindWidget))
    USlider* SoundSlider;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SoundValueTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* MusicValueTextBlock;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;
    UPROPERTY(meta = (BindWidget))
    UButton* LangRuButton;
    UPROPERTY(meta = (BindWidget))
    UButton* LangEnButton;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* FullScreenCheckBox;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScreenModeTextBlock;

    UPROPERTY(meta = (BindWidget))
    UButton* ScreenArrowRightButton;
    UPROPERTY(meta = (BindWidget))
    UButton* ScreenArrowLeftButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QualityArrowLeftButton;
    UPROPERTY(meta = (BindWidget))
    UButton* QualityArrowRightButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* QualityModeTextBlock;

    virtual void NativeOnInitialized() override;

private:
    TArray<FText> ArrayQualityText;
    UMSBJGameInstance* GameInst;
    UGameUserSettings* UserSettings;
    AMenuSystemByJamGameModeBase* GameMode;

    UFUNCTION()
    void OnChangedMusicSlider(float Value);

    UFUNCTION()
    void OnChangedSoundSlider(float Value);

    UFUNCTION()
    void OnComeBack();

    UFUNCTION()
    void OnFullScreenCheck(bool bIsChecked);

    UFUNCTION()
    void OnRuLangChanged();

    UFUNCTION()
    void OnEnLangChanged();

    UFUNCTION()
    void OnClickScreenArrowLeft();

    UFUNCTION()
    void OnClickScreenArrowRight();

    UFUNCTION()
    void OnClickQualityArrowLeft();

    UFUNCTION()
    void OnClickQualityArrowRight();

    void ChangeQualitySettings(int32 Index);
    void SetupStartSettings();
};
