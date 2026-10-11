// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupDatabase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartupDatabase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive,
                                                              int32 ApplyLevel)
{
	// WarriorASC가 없다는 건 게임 플레이 자체에 문제가 발생하므로 강제 크래시
	check(InWarriorASCToGive);
	
	GrantAbilities(ActivateOnGivenAbilities, InWarriorASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InWarriorASCToGive, ApplyLevel);
}

void UDataAsset_StartupDatabase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	
	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InWarriorASCToGive->GiveAbility(AbilitySpec);
	}
}
