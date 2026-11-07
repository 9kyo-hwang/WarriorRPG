// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

/*
 * 메타(임시) 어트리뷰트 처리 및 체력 연산. 예) 데미지 Clamp
 * 사망 처리(사망 이벤트 또는 애니메이션 트리거)
 * UI 및 시스템(파티클 등) 업데이트
 */
void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		
		const FString DebugString = FString::Printf(
			TEXT("OldHealth: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth);
		
		Debug::Print(DebugString, FColor::Green);
		
		// @TODO: Notify the UI
		
		// @TODO: Handle character death
		if (NewCurrentHealth == 0.f)
		{
			
		}
	}
}
