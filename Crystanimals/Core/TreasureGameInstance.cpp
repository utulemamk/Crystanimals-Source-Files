// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TreasureGameInstance.h"
#include "Player/AnimalCharacter.h"
#include "Kismet/GameplayStatics.h"

void UTreasureGameInstance::OnStart()
{
	ExistingCrystals =
	{
		"C01", "C02", "C03", "C04", "C05", "C06", "C07", "C08", "C09", "C10",
		"C11", "C12", "C13", "C14", "C15", "C16", "C17", "C18", "C19", "C20",
		"C21", "C22", "C23", "C24", "C25", "C26", "C27", "C28", "C29", "C30",
		"C31", "C32", "C33", "C34", "C35", "C36", "C37", "C38", "C39", "C40",
		"C41", "C42", "C43", "C44", "C45", "C46", "C47", "C48", "C49", "C50",
		"C51", "C52", "C53", "C54", "C55", "C56", "C57", "C58", "C59", "C60",
		"C61", "C62", "C63", "C64", "C65", "C66", "C67", "C68", "C69", "C70",
		"C71", "C72", "C73", "C74", "C75", "C76", "C77", "C78", "C79", "C80"
	};

	Score = 0;

	CurrentAnimal = EAnimal::Dog;

	bIsTrapdoorOpen = false;

	MouseSens = 1.0f;
}

void UTreasureGameInstance::ChangeRealm(FName RealmName)
{
	UGameplayStatics::OpenLevel(this, RealmName);
}
