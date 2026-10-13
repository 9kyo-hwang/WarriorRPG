// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include <AbilitySystem/WarriorAbilitySystemComponent.h>

/*
 * ASC에 어빌리티가 부여된 직후 호출
 * FGameplayAbilityActorInfo: 어빌리티를 사용하는 액터의 연관 데이터 캐싱 구조체
 * FGameplayAbilitySpec: 어빌리티 명세(활성화 여부 등)
 */
void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	// OnGiven 활성화 정책 어빌리티는 주어지는 즉시 활성화를 시도
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	// OnGiven 활성화 정책 어빌리티는 종료 시 ASC에서 즉시 제거
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}
