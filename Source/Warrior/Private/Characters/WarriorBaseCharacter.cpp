// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorBaseCharacter.h"
#include <AbilitySystem/WarriorAbilitySystemComponent.h>
#include <AbilitySystem/WarriorAttributeSet.h>

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;	// Tick 불필요
	PrimaryActorTick.bStartWithTickEnabled = false;	// 시작할 때도 Tick 불필요
	
	GetMesh()->bReceivesDecals = false;	// 이후 추가될 일부 VFX가 바닥에 데칼 투시하는데, 캐릭터는 무시하도록
	
	WarriorAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(FName("WarriorAttributeSet"));
}

UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (WarriorAbilitySystemComponent)
	{
		// 여기서는 컴포넌트 소유 액터 == 월드에 배치되는 액터
		WarriorAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

