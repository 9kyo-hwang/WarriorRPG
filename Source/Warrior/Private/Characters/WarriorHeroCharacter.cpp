// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorHeroCharacter.h"

#include <WarriorDebugHelper.h>

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	// 어깨 뒤 가깝게 + 약간 우상단 오프셋
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0, 55, 65);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);	// SpringArm의 끝을 나타내는 소켓 이름
	FollowCamera->bUsePawnControlRotation = false;	// CameraBoom이 폰 회전 따라가고, 카메라는 Boom 따라서...
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Debug::Print(TEXT("working"));
}
