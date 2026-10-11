// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorHeroCharacter.h"

#include <WarriorDebugHelper.h>

#include "EnhancedInputSubsystems.h"
#include "WarriorGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Input/WarriorInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

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

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (WarriorAbilitySystemComponent && WarriorAttributeSet)
	{
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, Avatar Actor: %s"), *WarriorAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *WarriorAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		
		Debug::Print(TEXT("AbilitySystemComponent valid. ") + ASCText, FColor::Green);
		Debug::Print(TEXT("AttributeSet valid."), FColor::Green);
	}
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data aasset as input config"));
	
	// 1. add IMC 2. IA for Callbacks
	if (ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		check(Subsystem);
		
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
		
		// 실패하면 즉시 크래시
		UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);
		WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	}
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
	
	if (MovementVector.Y != 0)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	
	if (LookAxisVector.Y != 0)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
