// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());

	// Editor에서도 해당 함수를 호출하며, 에디터에서 확인 가능한 변수 -> check 어설트 X
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	// Initialize에서 제대로 가져왔는지 검사
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	
	// 매 애니메이션 업데이트마다 이동 속도와 가속도 확인
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0;
}
