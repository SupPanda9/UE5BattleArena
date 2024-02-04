// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnPlayClicked();

protected:
	// Override the Initialize function
	virtual bool Initialize() override;

	// Declare two UButton pointers and use the BindWidget meta specifier
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

};
