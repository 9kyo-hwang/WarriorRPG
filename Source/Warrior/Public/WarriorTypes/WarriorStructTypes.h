// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WarriorStructTypes.generated.h"

USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink;
};