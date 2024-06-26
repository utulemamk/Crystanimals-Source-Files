// Fill out your copyright notice in the Description page of Project Settings.


#include "World/LevelPortal.h"
#include "Core/TreasureGameInstance.h"
#include "Player/AnimalPlayerController.h"

// Sets default values
ALevelPortal::ALevelPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void ALevelPortal::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("LevelPortal unable to get reference to GameInstance"));
	
	InteractableData = InstanceInteractableData;
}

// Called every frame
void ALevelPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelPortal::Interact()
{
	if (!DestinationRealm.IsNone())
	{
		GetWorld()->GetFirstPlayerController<AAnimalPlayerController>()->FadeToBlack();

		FTimerHandle TempTimer;
		GetWorldTimerManager().SetTimer(TempTimer,
			this,
			&ALevelPortal::ChangeRealm,
			1.1f,
			false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DestinationRealm has not been set for this actor"));
	}
}

void ALevelPortal::ChangeRealm()
{
	GameInstance->bShouldSaveAfterRealmChange = true;
	GameInstance->ChangeRealm(DestinationRealm);
}

