// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;

UENUM(BlueprintType)	// BP에서 컨트롤하고 싶다면
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	// 적들도 무기를 갖는데, 손 그 자체가 무기가 될 수도 있음
	LeftHand,
	RightHand,
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	// 등록할 무기 태그. 회수할 때도 사용
	// Hero가 무기 등록할 때는 false로, 적은 생성된 직후 무기를 장착하도록 true
	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category="Warrior|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);
	
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
protected:
	TArray<TObjectPtr<AActor>> OverlappedActors;
	
private:
	// 적, 플레이어 모두 가능해야 하는 동작: 소환된 무기 저장
	// 기본적으로 캐릭터는 무기 1개만 갖지만, 이 구조로 인해 2개 이상의 무기를 저장할 수 있음
	TMap<FGameplayTag, TObjectPtr<AWarriorWeaponBase>> CharacterCarriedWeaponMap;
};
