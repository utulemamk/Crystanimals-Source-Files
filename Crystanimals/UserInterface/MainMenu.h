// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward Declarations
class UButton;
class UEditableTextBox;
class UTreasureGameInstance;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ResetButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> MouseSensBox = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UFUNCTION()
	void ResetGameProgress();
	UFUNCTION()
	void ExitGame();
	UFUNCTION()
	void ChangeMouseSens(const FText& NewText, ETextCommit::Type TextType);
	
	virtual void NativeConstruct() override;
};
