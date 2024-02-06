// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGHUD.h"
#include "UI/EndGameWidget.h"
#include "UI/WinGameWidget.h"
#include "Kismet/GameplayStatics.h"

void AUE5TopDownARPGHUD::BeginPlay()
{
  Super::BeginPlay();

  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (IsValid(PlayerController))
  {
    WinGameWidget = CreateWidget<UWinGameWidget>(PlayerController, WinGameWidgetClass);
    EndGameWidget = CreateWidget<UEndGameWidget>(PlayerController, EndGameWidgetClass);
    if (IsValid(WinGameWidget))
    {
        WinGameWidget->AddToViewport();
        WinGameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    if (IsValid(EndGameWidget))
    {
        EndGameWidget->AddToViewport();
        EndGameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
  }

}

void AUE5TopDownARPGHUD::ShowWinGameScreen()
{
    if (IsValid(WinGameWidget))
    {
        WinGameWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AUE5TopDownARPGHUD::ShowEndGameScreen()
{
  if (IsValid(EndGameWidget))
  {
    EndGameWidget->SetVisibility(ESlateVisibility::Visible);
  }
}