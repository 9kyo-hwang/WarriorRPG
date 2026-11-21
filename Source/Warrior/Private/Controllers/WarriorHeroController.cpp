// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WarriorHeroController.h"

AWarriorHeroController::AWarriorHeroController()
{
	// Hero는 Id 0
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
