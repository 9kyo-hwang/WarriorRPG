// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <NativeGameplayTags.h>

namespace WarriorGameplayTags
{
	// 외부 모듈에서 접근 가능하도록 DLLEXPORT(WARRIOR_API) 필요
	
	/*************** 입력용 태그 ***************/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);
	
	/*************** 플레이어 전용 태그 ***************/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);			// HitPause 이벤트 트리거
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);	// 무기 등록에 사용할 태그
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	// 강공격 막타로 건너뛰는 태그
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);
	
	/*************** 적 전용 태그 ***************/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);	// 이 둘은
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);	// 후반부에 사용
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	
	/*************** 공용 태그 ***************/
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);		// HitReact 이벤트 트리거
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);		// 사망은 둘 다 가능
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);			// 체력이 0이면 추가될 태그
}

