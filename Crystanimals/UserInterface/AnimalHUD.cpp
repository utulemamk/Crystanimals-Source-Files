// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/AnimalSelectionMenu.h"
#include "UserInterface/InteractionWidget.h"
#include "UserInterface/StaticWidgetBase.h"
#include "UserInterface/ScoreWidget.h"
#include "UserInterface/ConfirmationWidget.h"
#include "UserInterface/StatBarWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Core/TreasureGameInstance.h"

AAnimalHUD::AAnimalHUD()
{
}

void AAnimalHUD::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("AnimalHUD unable to get reference to GameInstance"));

	GameInstance->OnScoreUpdated.AddDynamic(this, &AAnimalHUD::DisplayNewUnlocksWidget);

	GameInstance->OnUnlocksClaimed.AddDynamic(this, &AAnimalHUD::HideNewUnlocksWidget);

	GameInstance->OnGameSaved.AddDynamic(this, &AAnimalHUD::DisplayGameSavedWidget);

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	} 

	if (AnimalSelectionMenuClass)
	{
		AnimalSelectionMenuWidget = CreateWidget<UAnimalSelectionMenu>(GetWorld(), AnimalSelectionMenuClass);
		AnimalSelectionMenuWidget->AddToViewport(4);
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (OutOfBoundsWidgetClass)
	{
		OutOfBoundsWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), OutOfBoundsWidgetClass);
		OutOfBoundsWidget->AddToViewport();
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CrosshairClass)
	{
		Crosshair = CreateWidget<UStaticWidgetBase>(GetWorld(), CrosshairClass);
		Crosshair->AddToViewport(0);
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}

	if (NewUnlocksWidgetClass)
	{
		NewUnlocksWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), NewUnlocksWidgetClass);
		NewUnlocksWidget->AddToViewport();
		if (GameInstance->bNewUnlocksNotClaimed)
		{
			NewUnlocksWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else 
		{
			NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (NotEnoughSpaceWidgetClass)
	{
		NotEnoughSpaceWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), NotEnoughSpaceWidgetClass);
		NotEnoughSpaceWidget->AddToViewport();
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport(1);
		ScoreWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (ConfirmationWidgetClass)
	{
		ConfirmationWidget = CreateWidget<UConfirmationWidget>(GetWorld(), ConfirmationWidgetClass);
		ConfirmationWidget->AddToViewport(6);
		ConfirmationWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameSavedWidgetClass)
	{
		GameSavedWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), GameSavedWidgetClass);
		GameSavedWidget->AddToViewport(1);
		GameSavedWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (OxygenBarWidgetClass)
	{
		OxygenBarWidget = CreateWidget<UStatBarWidget>(GetWorld(), OxygenBarWidgetClass);
		OxygenBarWidget->AddToViewport(1);
		OxygenBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (OverheatBarWidgetClass)
	{
		OverheatBarWidget = CreateWidget<UStatBarWidget>(GetWorld(), OverheatBarWidgetClass);
		OverheatBarWidget->AddToViewport(1);
		OverheatBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayMainMenu()
{
	if (MainMenuWidget)
	{
		bIsMainMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		HideAnimalSelectionMenu();
		HideCrosshair();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AAnimalHUD::HideMainMenu()
{
	if (MainMenuWidget)
	{
		bIsMainMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayCrosshair();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AAnimalHUD::DisplayAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget && !bIsMainMenuVisible)
	{
		bIsAnimalSelectionMenuVisible = true;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AAnimalHUD::HideAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget)
	{
		bIsAnimalSelectionMenuVisible = false;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AAnimalHUD::DisplayInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::UpdateInteractionWidget(const FInteractableData InteractableData) const
{
	if (InteractionWidget && NewUnlocksWidget)
	{
		InteractionWidget->UpdateWidget(InteractableData);
		if (!InteractableData.bIsShop || NewUnlocksWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			DisplayInteractionWidget();
		}
	}
}

bool AAnimalHUD::InteractionWidgetIsVisible()
{
	return (InteractionWidget->GetVisibility() == ESlateVisibility::Visible) ? true : false;
}

void AAnimalHUD::DisplayOutOfBoundsWidget() const
{
	if (OutOfBoundsWidget)
	{
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideOutOfBoundsWidget() const
{
	if (OutOfBoundsWidget)
	{
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayCrosshair() const
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideCrosshair() const
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayNewUnlocksWidget()
{
	if (NewUnlocksWidget)
	{
		if (GameInstance->Score % 10 == 0)
		{
			GameInstance->bNewUnlocksNotClaimed = true;
			NewUnlocksWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AAnimalHUD::HideNewUnlocksWidget()
{
	if (NewUnlocksWidget)
	{
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
		HideInteractionWidget();
	}
}

void AAnimalHUD::DisplayNotEnoughSpaceWidget() const
{
	if (NotEnoughSpaceWidget)
	{
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle TempTimer;
		GetWorldTimerManager().SetTimer(TempTimer,
			this,
			&AAnimalHUD::HideNotEnoughSpaceWidget,
			1.5f,
			false);
	}
}

void AAnimalHUD::HideNotEnoughSpaceWidget() const
{
	if (NotEnoughSpaceWidget)
	{
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayScoreWidget() const
{
	if (ScoreWidget)
	{
		ScoreWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideScoreWidget() const
{
	if (ScoreWidget)
	{
		ScoreWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayConfirmationWidget(FString Action)
{
	if (ConfirmationWidget)
	{
		ConfirmationWidget->SetAction(Action);
		ConfirmationWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::DisplayGameSavedWidget()
{
	if (GameSavedWidget)
	{
		GameSavedWidget->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle,
			this,
			&AAnimalHUD::HideGameSavedWidget,
			1.5f,
			false);
	}
}

void AAnimalHUD::HideGameSavedWidget() const
{
	if (GameSavedWidget)
	{
		GameSavedWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::UpdateOxygenBarWidget(float CurrentValue, float MaxValue) const
{
	if (OxygenBarWidget)
	{
		OxygenBarWidget->UpdateStatBar(CurrentValue, MaxValue);
		
		if (OxygenBarWidget->GetVisibility() != ESlateVisibility::Visible)
		{
			OxygenBarWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AAnimalHUD::HideOxygenBarWidget() const
{
	if (OxygenBarWidget)
	{
		OxygenBarWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::UpdateOverheatBarWidget(float CurrentValue, float MaxValue) const
{
	
}

void AAnimalHUD::HideOverheatBarWidget() const
{

}
