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
	
	UFUNCTION(BlueprintCallable)
	void OnSliderValueChanged(float NewValue);
	
	UFUNCTION(BlueprintCallable)
	void OnCheckBoxChecked(bool CheckValue);
protected:
	// Override the Initialize function
	virtual bool Initialize() override;

	// Declare two UButton pointers and use the BindWidget meta specifier
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* Slider;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* CheckBox;
	
	UPROPERTY()
	int SliderValue;
};
