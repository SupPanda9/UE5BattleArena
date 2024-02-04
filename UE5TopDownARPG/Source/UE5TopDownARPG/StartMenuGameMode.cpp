// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuGameMode.h"
#include "UI/StartMenu.h"

void AStartMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    // Create the widget and store it in the variable
    //StartMenuWidgetClass = LoadClass<UStartMenu>(nullptr, TEXT("/Game/UI/StartMenu.StartMenu_C"));
    StartMenuWidget = CreateWidget<UStartMenu>(GetWorld(), StartMenuWidgetClass);

    // Check if the widget is valid
    if (StartMenuWidget)
    {
        // Add it to the viewport
        StartMenuWidget->AddToViewport();
        StartMenuWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

AStartMenuGameMode::AStartMenuGameMode() 
{

}


void AStartMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

}

