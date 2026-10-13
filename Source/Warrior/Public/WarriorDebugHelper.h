#pragma once

namespace Debug
{
	// DebugMessage + UE_LOG 같이 표시해주는 헬퍼 함수
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, Color, Message);
			
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}