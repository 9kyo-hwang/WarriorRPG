// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;
struct FGameplayTag;

UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes,
	No
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);
	
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);
	
	// 1. BP에서 함수 이름 표시될 때 BP_ 접두사 안보이도록 다르게 설정
	// 2. BP 전용 함수에서 Enum으로 결과를 확인할 수 있도록 Out Parameter 사용
	UFUNCTION(BlueprintCallable, Category="Warrior|FunctionLibrary", meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);
};
