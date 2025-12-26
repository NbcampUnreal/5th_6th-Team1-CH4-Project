#include "MonsterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{

}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity; //Movement에 Velocity 속력
		MoveSpeed = Velocity.Size2D(); //속력에 벡터의 2D 구성요소의 길이를 대입
		isFaling = Movement->IsFalling(); //땅에 땋인 여부 대입
	}
}
