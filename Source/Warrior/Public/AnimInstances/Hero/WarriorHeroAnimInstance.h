// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	// BP에 Hero 캐릭터를 표시하기 위함
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	TObjectPtr<class AWarriorHeroCharacter> OwningHeroCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|Locomotion")
	bool bShouldEnterRelaxState;
	
	// 5초 이상 Idle 상태가 지속되면 Relax 상태로 진입
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|Locomotion")
	float EnterRelaxStateThreshold = 5.f;
	
	float IdleElapsedTime;	// Idle 상태 유지 시간
};
