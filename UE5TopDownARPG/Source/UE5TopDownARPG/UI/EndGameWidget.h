// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Declare two UFUNCTIONs with the BlueprintCallable specifier
	UFUNCTION(BlueprintCallable)
	void OnPlayClicked();

	UFUNCTION(BlueprintCallable)
	void OnQuitClicked();

protected:
	// Override the Initialize function
	virtual bool Initialize() override;

	// Declare two UButton pointers and use the BindWidget meta specifier
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
