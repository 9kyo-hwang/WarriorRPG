// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WarriorAIController.h"

#include "WarriorDebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

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
	
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;		// 적 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;	// 아군 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;	// 중립 감지
	AISenseConfig_Sight->SightRadius = 5000.f;	// BP 조정 가능
	AISenseConfig_Sight->LoseSightRadius = 0.f;	// 적들은 절대 플레이어를 놓치지 않도록
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;	// 적 시야각
	
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
}
