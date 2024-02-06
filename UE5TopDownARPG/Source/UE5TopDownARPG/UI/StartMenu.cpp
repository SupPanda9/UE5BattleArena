// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "../BattleArenaGameInstance.h"
#include "../UE5TopDownARPG.h"

bool UStartMenu::Initialize()
{
	// Call the base class Initialize function
	bool success = Super::Initialize();
	if (!success) return false;

	// Check if the buttons are valid
	if (!ensure(PlayButton != nullptr)) return false;
	if (!ensure(Slider != nullptr)) return false;
	if (!ensure(CheckBox != nullptr)) return false;

	// Bind the OnClicked events of the buttons to the functions
	PlayButton->OnClicked.AddDynamic(this, &UStartMenu::OnPlayClicked);
	Slider->OnValueChanged.AddDynamic(this, &UStartMenu::OnSliderValueChanged);
	CheckBox->OnCheckStateChanged.AddDynamic(this, &UStartMenu::OnCheckBoxChecked);

	// Return true if everything is successful
	return true;
}

void UStartMenu::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TopDownMap");

	SetVisibility(ESlateVisibility::Collapsed);
}

void UStartMenu::OnSliderValueChanged(float NewValue)
{
	SliderValue = FMath::RoundToInt(NewValue);
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());

	if (GameInstance) {
		GameInstance->SetNumberOfWaves(SliderValue);
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("SliderValue %d"), SliderValue);
	}
}

void UStartMenu::OnCheckBoxChecked(bool CheckValue)
{
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());

	if (GameInstance) {
		GameInstance->SetIsInfinite(CheckValue);
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("CheckBox %s"), GameInstance->GetIsInfinite() ? TEXT("true") : TEXT("false"));
	}
}
