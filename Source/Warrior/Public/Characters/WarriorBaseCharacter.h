// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;

UCLASS()
class WARRIOR_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorBaseCharacter();
	
	// ASC를 사용하려면 해당 인터페이스를 반드시 구현해야 함
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// C++에서는 Getter를 통해 AbilitySystem에 접근
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return WarriorAbilitySystemComponent;}
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet;}
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
protected:
	// Blueprint에서는 아래 2가지 요소 접근 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UWarriorAbilitySystemComponent> WarriorAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UWarriorAttributeSet> WarriorAttributeSet;
};
