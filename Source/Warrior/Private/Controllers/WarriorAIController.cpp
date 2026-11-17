// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WarriorAIController.h"

#include "WarriorDebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"

/*
 * UE에서 기본 제공하는 DetourCrowdAIController도 아래와 동일한 동작을 수행함
 * PathFollowingComponent가 AI 길찾기에서 사용하는 컴포넌트로, 이 타입을 바꿔치기 하면 됨
 */
AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("UCrowdFollowingComponent valid"), FColor::Green);
	}
}
