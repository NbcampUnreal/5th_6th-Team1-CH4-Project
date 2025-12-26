#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerAnimInstance.h"
#include "Engine/GameEngine.h"
#include "Components/InputComponent.h"
#include "CMontagesComponent.h"
#include "CMovementComponent.h"
#include "BowAnimInstance.h"
#include "Arrow.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMesh
	(TEXT("/Script/Engine.SkeletalMesh'/Game/KoreanTraditionalMartialArts/Meshs/Characters/Meshs/SKM_Soldier_1.SKM_Soldier_1'"));

	if (PlayerMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMesh.Object);
		GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance
	(TEXT("/Game/Blueprints/Player/ABP_Player.ABP_Player_C"));

	if (AnimInstance.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	BowComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMesh"));
	//ArrowComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArrowMesh"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> BowMesh
	(TEXT("/Script/Engine.SkeletalMesh'/Game/BowAnimations/Bow/SK_ElvenBow.SK_ElvenBow'"));

	if (BowMesh.Succeeded())
	{
		BowComp->SetSkeletalMesh(BowMesh.Object);
		BowComp->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform, TEXT("Bow_LSocket"));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance> BowAnimInstance
	(TEXT("/Game/Blueprints/Weapon/ABP_Bow.ABP_Bow_C"));

	if (BowAnimInstance.Class)
	{
		BowComp->SetAnimInstanceClass(BowAnimInstance.Class);
	}

	// ConstructorHelpers::FObjectFinder<USkeletalMesh> ArrowMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/BowAnimations/Arrow/SM_ElvenArrow.SM_ElvenArrow'"));
	//if (ArrowMesh.Succeeded())
	//{
	//	ArrowComp->SetSkeletalMesh(ArrowMesh.Object);
	//	ArrowComp->AttachToComponent(GetMesh(),
	//		FAttachmentTransformRules::KeepRelativeTransform, TEXT("Arrow_RSocket"));
	//}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	if (SpringArm)
	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetWorldLocation(FVector(0, 0, 55));
		SpringArm->TargetArmLength = 150;
		SpringArm->SocketOffset = FVector(0, 100, 0);
		GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	}
	
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_DefaultInput.IMC_DefaultInput'"));
	if (InputContext.Succeeded())
	{
		DefaultContext = InputContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));

	if (InputMove.Succeeded())
	{
		MoveAction = InputMove.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputLook(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Look.IA_Look'"));
	if (InputLook.Succeeded())
	{
		LookAction = InputLook.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputBowChange(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_BowChange.IA_BowChange'"));
	if (InputBowChange.Succeeded())
	{
		BowChangeAction = InputBowChange.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputAxChange(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_GunChange.IA_GunChange'"));
	if (InputAxChange.Succeeded())
	{
		GunChangeAction = InputAxChange.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputFire(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Fire.IA_Fire'"));
	if (InputFire.Succeeded())
	{
		FireAction = InputFire.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>
		InputAim(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Aim.IA_Aim'"));
	if (InputAim.Succeeded())
	{
		AimAction = InputAim.Object;
	}

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultContext, 0);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = 600;

	//BowComp->SetVisibility(false);
	//if (BowComp)
	//{		
	//	
	//}

	CharacterMovement->MaxWalkSpeed = 600; //Walk
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction,
		ETriggerEvent::Triggered,
		this,
		&APlayerCharacter::Move);

	EnhancedInputComponent->BindAction(LookAction,
		ETriggerEvent::Triggered,
		this,
		&APlayerCharacter::Look);

	EnhancedInputComponent->BindAction(BowChangeAction,
		ETriggerEvent::Started,
		this,
		&APlayerCharacter::BowChange);

	EnhancedInputComponent->BindAction(GunChangeAction,
		ETriggerEvent::Started,
		this,
		&APlayerCharacter::GunChange);

	EnhancedInputComponent->BindAction(AimAction,
		ETriggerEvent::Started,
		this,
		&APlayerCharacter::OnAim);

	EnhancedInputComponent->BindAction(AimAction,
		ETriggerEvent::Completed,
		this,
		&APlayerCharacter::OffAim);

	EnhancedInputComponent->BindAction(FireAction,
		ETriggerEvent::Started,
		this,
		&APlayerCharacter::Fire);

}

//AArrow* APlayerCharacter::GetAttachedArrow()
//{
//	//for (AArrow* projectile : Arrows)
//	//{
//	//	if (!!projectile->GetAttachParentActor())
//	//		return projectile;
//	//}
//	//return nullptr;
//}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	const FVector2D Movement = value.Get<FVector2D>();

	const FRotator ControlRot =
		Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;

	const FRotator YawOnly(0.f, ControlRot.Yaw, 0.f);

	const FVector Forward = UKismetMathLibrary::GetForwardVector(YawOnly);
	const FVector Right = UKismetMathLibrary::GetRightVector(YawOnly);
	AddMovementInput(Forward, Movement.Y);
	AddMovementInput(Right, Movement.X);
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y * GetWorld()->DeltaRealTimeSeconds * mouseSpeed);
	AddControllerYawInput(LookAxisVector.X * GetWorld()->DeltaRealTimeSeconds * mouseSpeed);
}

void APlayerCharacter::BowChange()
{
	UPlayerAnimInstance* Ani = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (Ani)
	{
		//Ani->Montage_Play(AM_Equip);
	}

	//if (BowComp)
	//{
	//	BowComp->SetVisibility(true);
	//}
}

void APlayerCharacter::GunChange()
{
	
}

void APlayerCharacter::OnAim()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!! Player")));
	//if (CurrentHandWeapon == EWeaponTypes::None)
	//	return;

	UPlayerAnimInstance* Ani = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (Ani)
	{
		Ani->isAim = true;
		//Ani->PlayerAnimSequence = BowAnim;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!! Player")));
		//SpringArm->bUsePawnControlRotation = false;
		//if (ArrowComp)
		//{
		//	ArrowComp->SetVisibility(true);
		//}
	}

}

void APlayerCharacter::OffAim()
{
	UPlayerAnimInstance* Ani = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (Ani)
	{
		Ani->isAim = false;
		//SpringArm->bUsePawnControlRotation = true;
	}
}

void APlayerCharacter::Fire()
{
	TestFunction();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire")));

	//if (ArrowComp)
	//{
	//	ArrowComp->SetVisibility(false);
	//}

	//AArrow* arrow = GetAttachedArrow();
	//arrow->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	//FVector forward = FQuat(OwnerCharacter->GetControlRotation()).GetForwardVector();
	//arrow->Shoot(forward);
	

	//AArrow* arrow = 
	//UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//if (AnimInstance && AnimInstance->isAim && !IsFire)
	//{
	//	if (WeaponFireMontages[CurrentHandWeapon] && WeaponFireMontages.Contains(CurrentHandWeapon))
	//	{
	//		AnimInstance->Montage_Play(WeaponFireMontages[CurrentHandWeapon]);
	//		if (WeaponFireMontages[CurrentHandWeapon] && WeaponTypeSkeletalMeshes.Contains(CurrentHandWeapon))
	//		{
	//			SpawnMuzzleFX(WeaponTypeSkeletalMeshes[CurrentHandWeapon], BowMuzzleFX);
	//			FHitResult Hit;
	//			FVector StartTrace = Camera->GetComponentLocation();
	//			FVector EndTrace = StartTrace + (Camera->GetForwardVector() * WeaponDistance);
	//			TArray<AActor*> IgnorActors;
	//			ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1);

	//			bool Result = UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartTrace, EndTrace,
	//				ETraceTypeQuery::TraceTypeQuery1, false, IgnorActors, EDrawDebugTrace::ForDuration, Hit, true,
	//				FLinearColor::Red, FLinearColor::Green, 3.0f);

	//			//TraceTypeQuery1 == TraceChannel 0

	//			if (Result)
	//			{
	//				Hit.GetActor()->Destroy();
	//			}
	//		}

	//		// 활을 쏠 때 활줄을 원래대로 복원
	//		if (CurrentHandWeapon == EWeaponType::BowWeapon)
	//		{
	//			if (ArrowMesh && ArrowMesh->GetAnimInstance())
	//			{
	//				if (UBowAnimInstance* BowAnimInstance = Cast<UBowAnimInstance>(ArrowMesh->GetAnimInstance()))
	//				{
	//					if (float* BendValue = BowAnimInstance->GetBend())
	//					{
	//						*BendValue = 0.0f; // 활을 쏜 후 활줄 복원
	//					}
	//				}
	//			}
	//		}

	//		IsFire = true;
	//	}
	//	//else if (AM_MatchlockgunFire && CurrentHandWeapon == EWeaponType::Matchlockgun)
	//	//{
	//	//	AnimInstance->Montage_Play(AM_MatchlockgunFire);
	//	//	IsFire = true;
	//	//}

	//	FTimerHandle WeaponDelayHandle;
	//	GetWorld()->GetTimerManager().SetTimer(
	//		WeaponDelayHandle,
	//		[this]() {
	//			IsFire = false;
	//		},
	//		WeaponDelayCount,
	//		false);
	//}
}
