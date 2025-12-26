#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UCLASS()
class TPSWARSURVIVE_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override; // 애니메이션이 생성되면 호출 함수

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 프레임마다 호출 함수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class ACharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UCharacterMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity; //Movement에 velocity 속력을 저장하는 변수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveSpeed; //속력에 벡터의 2D 구성요소의 길이를 저장하는 변수

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool isFaling = false; // Gruound에 닿여 있는에 대한 여부 저장 변수
};
