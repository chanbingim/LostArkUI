// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "PlayerDataSubSystem.h"
#include "Actors/ActorsDataTable/ActorDataTableBase.h"

void UMyGameInstance::Init()
{
	Super::Init();

	auto playerDataSystem = GetSubsystem<UPlayerDataSubSystem>();
	playerDataSystem->Init();

	UE_LOG(LogTemp, Warning, TEXT("Instance Init"));
}
