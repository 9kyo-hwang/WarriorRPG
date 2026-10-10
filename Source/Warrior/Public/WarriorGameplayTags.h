// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <NativeGameplayTags.h>

namespace WarriorGameplayTags
{
	// Input Tags
	
	// 외부 모듈에서 접근 가능하도록 DLLEXPORT(WARRIOR_API) 필요
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
}