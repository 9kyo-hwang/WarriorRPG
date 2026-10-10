// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorBaseCharacter.h"

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;	// Tick 불필요
	PrimaryActorTick.bStartWithTickEnabled = false;	// 시작할 때도 Tick 불필요
	
	GetMesh()->bReceivesDecals = false;	// 이후 추가될 일부 VFX가 바닥에 데칼 투시하는데, 캐릭터는 무시하도록
}

