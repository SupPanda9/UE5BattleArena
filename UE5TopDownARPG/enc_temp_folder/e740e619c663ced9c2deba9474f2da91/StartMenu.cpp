// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
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

	// Bind the OnClicked events of the buttons to the functions
	PlayButton->OnClicked.AddDynamic(this, &UStartMenu::OnPlayClicked);
	Slider->OnValueChanged.AddDynamic(this, &UStartMenu::OnSliderValueChanged);

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
	SliderValue = FMath::RoundToInt(1+(NewValue*19));
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());

	if (GameInstance) {
		GameInstance->SetNumberOfWaves(SliderValue);
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("SliderValue %f"), SliderValue);
	}
}