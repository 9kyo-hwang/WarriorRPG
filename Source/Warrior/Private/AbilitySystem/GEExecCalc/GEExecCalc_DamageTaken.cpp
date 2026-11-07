// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAttributeSet.h"

#include "WarriorDebugHelper.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	
	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false)	// 내 공격력
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefensePower, Target, false)	// 상대 방어력
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false)	// 상대에게 적용할 어트리뷰트
	}
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;	
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/* 요소 하나하나 추가하는 방식. 구조체와 매크로를 통해 쉽게 처리할 수 있음
		FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(UWarriorAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, AttackPower));
		FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(AttackPowerProperty, EGameplayEffectAttributeCaptureSource::Source, false);
		RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);
	 */
	
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);	
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);	
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	// 캡처한 어트리뷰트 크기를 계산
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);
	
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
		
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);
	
	/************ 데미지 계산 ***************/
	if (UsedLightAttackComboCount != 0)
	{
		// 약공격 2타부터 피해량 5%p 증가: 1.00, 1.05, 1.1, 1.15
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}
	
	if (UsedHeavyAttackComboCount != 0)
	{
		// 강공격은 1타부터 피해량 15%p씩 증가: 1.15, 1.3
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}
	
	// 단순하면서 깔끔한 수식, 적에게도 똑같이 적용 가능(단 적은 콤보 카운트가 없어서 바로 여기로 직행)
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);
	
	if (FinalDamageDone > 0.f)
	{
		// 데미지 계산이 완료됐으니 Attribute에 변화를 줘야 함
		// 단 직접 수행하지는 않고, 임시(Placeholder) Attribute를 가지고 수행: 바로 적용하기 전에 Clamp 같은 거 적용할 수 있음
		
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWarriorDamageCapture().DamageTakenProperty, 
				EGameplayModOp::Override,
				FinalDamageDone));
	}
}
