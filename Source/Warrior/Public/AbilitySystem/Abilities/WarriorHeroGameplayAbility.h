// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class AWarriorHeroCharacter;
class AWarriorHeroController;
class UHeroCombatComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()
	
public:
	// Hero Character 반환하는 Helper
	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();
	
	// Hero Controller 반환하는 Helper
	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	AWarriorHeroController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
private:
	// HeroCharacter는 자주 사용될 건데, 매번 캐스팅하는 것보단 캐싱해두는 것이 좋음
	// 약참조로 가리키기(AbilityActorInfo 내부에서도 이렇게 사용)
	TWeakObjectPtr<AWarriorHeroCharacter> CachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarriorHeroController> CachedWarriorHeroController;
};
