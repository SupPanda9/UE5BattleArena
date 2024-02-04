// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UStartMenu::Initialize()
{
	// Call the base class Initialize function
	bool success = Super::Initialize();
	if (!success) return false;

	// Check if the buttons are valid
	if (!ensure(PlayButton != nullptr)) return false;

	// Bind the OnClicked events of the buttons to the functions
	PlayButton->OnClicked.AddDynamic(this, &UStartMenu::OnPlayClicked);

	// Return true if everything is successful
	return true;
}

void UStartMenu::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TopDownMap");

	SetVisibility(ESlateVisibility::Collapsed);
}