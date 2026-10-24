// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARRIOR_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	// 컴포넌트 오너를 쉽게 확인하도록.
	template<class T>
	T* GetOwningPawn() const
	{
		// T가 Pawn의 자식인지 정적 검사
		static_assert
		(
			TPointerIsConvertibleFromTo<T, APawn>::Value, 
			"'T' Template Parameter get GetPawn must be derived from APawn"
		);
		
		// 실패하면 crash
		return CastChecked<T>(GetOwner());
	}
	
	// Hero나 Enemy가 아닌 단순 Pawn으로 획득하고자 한다면 얘로
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}
	
	// 컴포넌트 오너 컨트롤러.
	template<class T>
	T* GetOwningController() const
	{
		static_assert
		(
			TPointerIsConvertibleFromTo<T, AController>::Value, 
			"'T' Template Parameter get GetController must be derived from AController"
		);
		
		return GetOwningPawn()->GetController<T>();
	}
	
	// 필요하다면 게임모드, 게임 인스턴스, 플레이어 스테이트, 게임 스테이트 등에 대해서도 추가
};
