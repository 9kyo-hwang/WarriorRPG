// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarriorHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	// 오너 컴포넌트(스켈레탈 메시 컴포넌트)로부터 AnimInstance를 받아 캐스팅
	// 그런데 얘 자체가 AnimInstance인데, SkeletalMeshComponent를 거쳐서 다시 AnimInstance 가져오는 게 다른 건가?
	return Cast<UWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
