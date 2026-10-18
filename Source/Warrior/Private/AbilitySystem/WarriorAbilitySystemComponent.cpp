// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// HeroStartupData의 GiveToASC에서 DynamicAbilityTags에 InputTag를 추가해둔 상태라 검색 가능
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
}

void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}
	
	/*
	 * 무기 장착 시 장착 해제 GA를 부여
	 * 장착 해제 시, 기존에 부여했던 어빌리티들을 모두 제거: GA의 EndAbility에서 수행
	 * - EndAbility는 ActorInfo->ASC->ClearAbility(Handle) 형태로 어빌리티를 제거함
	 * - 즉 어빌리티 스펙 "핸들"이 필요함
	 * 
	 * 현재 GiveAbility를 보면 어빌리티 스펙 핸들을 반환하고 있음
	 * - 즉 GiveAbility 반환값인 핸들을 "저장"하고,
	 * - 추후 장착 해제 시 저장한 핸들을 가지고 ClearAbility()를 호출하는 구조로 변경해야 함
	 */
	
	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (AbilitySet.IsValid())
		{
			FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
			AbilitySpec.SourceObject = GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
			
			// 수정: 무기 어빌리티 부여 함수 호출자는 부여한 어빌리티들의 핸들을 배열로 관리
			OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
		}
	}
}
