// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AnimalHUD.generated.h"

// Forward Declarations
class UMainMenu;
class UAnimalSelectionMenu;
class UInteractionWidget;
class UStaticWidgetBase;
class UScoreWidget;
class UConfirmationWidget;
class UStatBarWidget;
class UEditableNotificationWidget;
class UFreezeOverlayWidget;
class UMainMenuPage;
class UTreasureGameInstance;
struct FInteractableData;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API AAnimalHUD : public AHUD
{
	GENERATED_BODY()

public:

	// These are defined in the editor as WidgetBlueprints with actual graphics
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UAnimalSelectionMenu> AnimalSelectionMenuClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> OutOfBoundsWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> CrosshairClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> NewUnlocksWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> NotEnoughSpaceWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UScoreWidget> ScoreWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UConfirmationWidget> ConfirmationWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> GameSavedWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStatBarWidget> OxygenBarWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStatBarWidget> ExhaustionBarWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UEditableNotificationWidget> NowUnlockedWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UFreezeOverlayWidget> FreezeOverlayWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> CannotChangeWhileFallingWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> TrapdoorLockedWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UStaticWidgetBase> TrapdoorUnlockedWidgetClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenuPage> HowToPlayPageClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenuPage> CreditsPageClass = nullptr;

	UPROPERTY()
	bool bIsMainMenuVisible;
	UPROPERTY()
	bool bIsAnimalSelectionMenuVisible;

	AAnimalHUD();

	UFUNCTION()
	void DisplayMainMenu();
	UFUNCTION()
	void HideMainMenu();

	UFUNCTION()
	void DisplayAnimalSelectionMenu();
	UFUNCTION()
	void HideAnimalSelectionMenu();

	UFUNCTION()
	void DisplayInteractionWidget() const;
	UFUNCTION()
	void HideInteractionWidget() const;
	UFUNCTION()
	void UpdateInteractionWidget(const FInteractableData InteractableData) const;
	UFUNCTION()
	bool InteractionWidgetIsVisible();

	UFUNCTION()
	void DisplayOutOfBoundsWidget() const;
	UFUNCTION()
	void HideOutOfBoundsWidget() const;

	UFUNCTION()
	void DisplayCrosshair() const;
	UFUNCTION()
	void HideCrosshair() const;

	UFUNCTION()
	void UpdateNewUnlocksWithDelay();
	UFUNCTION()
	void UpdateNewUnlocks();
	UFUNCTION()
	void DisplayNewUnlocksWidget();
	UFUNCTION()
	void HideNewUnlocksWidget();

	UFUNCTION()
	void DisplayNotEnoughSpaceWidget() const;
	UFUNCTION()
	void HideNotEnoughSpaceWidget() const;

	UFUNCTION()
	void DisplayScoreWidget() const;
	UFUNCTION()
	void HideScoreWidget() const;

	UFUNCTION()
	void DisplayConfirmationWidget(FString Action);
	UFUNCTION()
	void HideConfirmationWidget() const;

	UFUNCTION()
	void DisplayGameSavedWidget();
	UFUNCTION()
	void HideGameSavedWidget() const;

	UFUNCTION()
	void UpdateOxygenBarWidget(float CurrentValue, float MaxValue) const;
	UFUNCTION()
	void HideOxygenBarWidget() const;

	UFUNCTION()
	void UpdateExhaustionBarWidget(float CurrentValue, float MaxValue) const;

	UFUNCTION()
	void DisplayNowUnlockedWidget(FString TextToDisplay) const;
	UFUNCTION()
	void HideNowUnlockedWidget() const;

	UFUNCTION()
	void SetFreezeOverlayOpacity(float InOpacity) const;
	UFUNCTION()
	void FadeFreezeOverlayOpacityToZero(float InOpacity) const;

	UFUNCTION()
	void DisplayCannotChangeWhileFallingWidget() const;
	UFUNCTION() 
	void HideCannotChangeWhileFallingWidget() const;

	UFUNCTION()
	void DisplayTrapdoorLockedWidget() const;
	UFUNCTION()
	void HideTrapdoorLockedWidget() const;

	UFUNCTION()
	void DisplayTrapdoorUnlockedWidget() const;
	UFUNCTION()
	void HideTrapdoorUnlockedWidget() const;

	UFUNCTION()
	void DisplayHowToPlayPage();
	UFUNCTION()
	void DisplayCreditsPage();
	UFUNCTION()
	void HideMainMenuPages();



protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UAnimalSelectionMenu> AnimalSelectionMenuWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UInteractionWidget> InteractionWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> OutOfBoundsWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> Crosshair = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> NewUnlocksWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> NotEnoughSpaceWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UScoreWidget> ScoreWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UConfirmationWidget> ConfirmationWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> GameSavedWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStatBarWidget> OxygenBarWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStatBarWidget> ExhaustionBarWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UEditableNotificationWidget> NowUnlockedWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UFreezeOverlayWidget> FreezeOverlayWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> CannotChangeWhileFallingWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> TrapdoorLockedWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStaticWidgetBase> TrapdoorUnlockedWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UMainMenuPage> HowToPlayPage = nullptr;
	
	UPROPERTY()
	TObjectPtr<UMainMenuPage> CreditsPage = nullptr;



	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> PositiveNotificationSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> NegativeNotificationSound = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;
	
};
