// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MSBJMenuHUD.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MenuSystemByJam/MenuSystemByJamGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJMenuHUD, All, All);

void AMSBJMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld() || !this->MenuHudWidgetClass || !this->OptionsHudWidgetClass || !this->CreditsHudWidgetClass)
	{
		UE_LOG(LogMSBJMenuHUD, Error, TEXT("Founded in BeginPlay nullptr!"));
		return;
	}
	
	this->GameWidgets.Add(EMSBJGameMenuState::InProgress, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->MenuHudWidgetClass));
	this->GameWidgets.Add(EMSBJGameMenuState::Options, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->OptionsHudWidgetClass));
	this->GameWidgets.Add(EMSBJGameMenuState::Credits, CreateWidget<UMSBJBaseWidget>(GetWorld(), this->CreditsHudWidgetClass));

	for (auto Widget : this->GameWidgets)
	{
		const auto ValueWidget = Widget.Value;
		ValueWidget->AddToViewport();
		ValueWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	const auto GameMode = Cast<AMenuSystemByJamGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		UE_LOG(LogMSBJMenuHUD, Error, TEXT("Game Mode is nullptr"));
		return;
	}
		GameMode->OnGameMenuStateChangedSignature.AddUObject(this, &AMSBJMenuHUD::OnGameStateChanged);
}

void AMSBJMenuHUD::OnGameStateChanged(EMSBJGameMenuState NewState)
{
	if(this->CurrentWidget)
	{
		this->CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (this->GameWidgets.Contains(NewState))
	{
		this->CurrentWidget = this->GameWidgets[NewState];
	}
	if (this->CurrentWidget)
	{
		this->CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		this->CurrentWidget->Show();
	}
	UE_LOG(LogMSBJMenuHUD, Display, TEXT("New State: %s"), *UEnum::GetValueAsString(NewState))
}
