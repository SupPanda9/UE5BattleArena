// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGHUD.h"
#include "UI/EndGameWidget.h"
#include "UI/WinGameWidget.h"
#include "UI/GameStatisticsWidget.h"
#include "Kismet/GameplayStatics.h"

void AUE5TopDownARPGHUD::BeginPlay()
{
  Super::BeginPlay();

  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (IsValid(PlayerController))
  {
    GameStatisticsWidget = CreateWidget<UGameStatisticsWidget>(PlayerController, GameStatisticsWidgetClass);
    WinGameWidget = CreateWidget<UWinGameWidget>(PlayerController, WinGameWidgetClass);
    EndGameWidget = CreateWidget<UEndGameWidget>(PlayerController, EndGameWidgetClass);
    if (IsValid(GameStatisticsWidget))
    {
        GameStatisticsWidget->AddToViewport();
        GameStatisticsWidget->SetVisibility(ESlateVisibility::Visible);
    }
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

void AUE5TopDownARPGHUD::UpdateGameStatistics()
{
    GameStatisticsWidget->SetValues();
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
        EndGameWidget->SetEndScore();
        EndGameWidget->SetVisibility(ESlateVisibility::Visible);
    }
}