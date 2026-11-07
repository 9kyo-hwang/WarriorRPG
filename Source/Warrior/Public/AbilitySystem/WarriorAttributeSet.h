// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include <AbilitySystem/WarriorAbilitySystemComponent.h>
#include "WarriorAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)               

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UWarriorAttributeSet();
	
	/**
	 *	GE가 실행되어 어트리뷰트 BaseValue 수정 직후 호출. 이 시점에서는 이미 값이 확정되어 함수 내부에서 속성 값을 직접 되돌리거나 수정할 수 없음
	 *	실행(Execute) 단계에서만 호출. 버프(예: 5초동안 이동속도 10 증가)같은 적용(Application) 단계에서는 호출 X
	 */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category="Heatlh")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)
	
	UPROPERTY(BlueprintReadOnly, Category="Heatlh")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)
	
	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)
	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)
	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefensePower)
	
	// 데미지 적용 시 Taken 통해서 체력 변경: 임시(Placeholder) 어트리뷰트
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)
};
