// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FWarriorInputActionConfig& Config : NativeInputActions)
	{
		if (Config.InputTag == InInputTag && Config.InputAction)
		{
			return Config.InputAction;
		}
	}
	
	return nullptr;
}
