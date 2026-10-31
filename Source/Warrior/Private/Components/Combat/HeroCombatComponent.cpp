// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"

#include "Items/Weapons/WarriorHeroWeapon.h"
#include "WarriorGameplayTags.h"

#include "AbilitySystemBlueprintLibrary.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// PawnCombatComponent가 공격한 대상체 목록을 들고 있음
	// 공격 한 번당 1회만 피해를 입히도록 검사
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(HitActor);
	
	// 공격 애님 몽타주가 재생되면서 게임플레이 이벤트를 대기하고 있음
	// 이벤트를 날리자!
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Shared_Event_MeleeHit, Data);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	// Begin에서 등록한 HitActor를 지우는 작업은 PawnCombatComponent에서
	// ToggleWeaponCollision에서 충돌 판정 끌 때 한 번에 처리
}
