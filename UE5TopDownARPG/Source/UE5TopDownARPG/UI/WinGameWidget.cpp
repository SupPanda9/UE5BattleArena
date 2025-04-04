// Fill out your copyright notice in the Description page of Project Settings.


#include "WinGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UWinGameWidget::Initialize()
{
	// Call the base class Initialize function
	bool success = Super::Initialize();
	if (!success) return false;

	// Check if the buttons are valid
	if (!ensure(PlayButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;

	// Bind the OnClicked events of the buttons to the functions
	PlayButton->OnClicked.AddDynamic(this, &UWinGameWidget::OnPlayClicked);
	QuitButton->OnClicked.AddDynamic(this, &UWinGameWidget::OnQuitClicked);

	// Return true if everything is successful
	return true;
}

void UWinGameWidget::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "GameLevel");

	SetVisibility(ESlateVisibility::Collapsed);
}

void UWinGameWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}