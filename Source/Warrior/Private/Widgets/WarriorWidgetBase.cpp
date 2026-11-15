// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WarriorWidgetBase.h"

#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	// 우선 Hero가 위젯 생성하는 부분 커버
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			// 호출 == 위젯 초기화됐고, HeroUIComponent가 유효함
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}
