// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDatabase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_StartupDatabase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// ApplyLevel: 난이도(메인 메뉴에서 변경 가능)
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel = 1);
	
protected:
	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive, UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;
	
	// 특정 조건에서 발동되는 Hit 반응 또는 사망 같은 어빌리티
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;
};
