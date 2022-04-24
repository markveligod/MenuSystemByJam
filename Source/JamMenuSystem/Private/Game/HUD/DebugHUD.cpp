/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "Game/HUD/DebugHUD.h"
#include "Engine/Canvas.h"

ADebugHUD::ADebugHUD()
{
    static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/Roboto"));

    MainFont = Font.Object;
}

void ADebugHUD::BeginPlay()
{
    Super::BeginPlay();
    this->ParamFont.FontObject = this->MainFont;
    this->ParamFont.Size = this->SizeFont;
}

void ADebugHUD::DrawHUD()
{
    this->X = this->DefaultX;
    this->Y = this->DefaultY;
}

void ADebugHUD::AddText(const TCHAR* title, const FText& value)
{
    RenderStatistic(title, value);
}

void ADebugHUD::AddFloat(const TCHAR* title, float value)
{
    RenderStatistic(title, FText::AsNumber(value));
}

void ADebugHUD::AddInt(const TCHAR* title, int32 value)
{
    RenderStatistic(title, FText::AsNumber(value));
}

void ADebugHUD::AddBool(const TCHAR* title, bool value)
{
    RenderStatistic(title, BoolToText(value), (value == false) ? FLinearColor::Red : FLinearColor::Green);
}

void ADebugHUD::RenderStatistic(const TCHAR* title, const FText& value, const FLinearColor& valueColor)
{
    FCanvasTextItem TitleItem(FVector2D(this->X, this->Y), CStringToText(title), this->ParamFont, this->TitleColor);
    TitleItem.EnableShadow(FLinearColor(0.0f, 0.0f, 0.0f));
    Canvas->DrawItem(TitleItem);

    FCanvasTextItem ValueItem(FVector2D(this->X + this->HorizontalOffset, this->Y), value, this->ParamFont, valueColor);
    ValueItem.EnableShadow(FLinearColor(0.0f, 0.0f, 0.0f));
    Canvas->DrawItem(ValueItem);
    this->Y += this->LineHeight;
}

FText ADebugHUD::CStringToText(const TCHAR* text)
{
    return FText::FromString(text);
}

FText ADebugHUD::BoolToText(bool value)
{
    return CStringToText((value == true) ? TEXT("true") : TEXT("false"));
}
