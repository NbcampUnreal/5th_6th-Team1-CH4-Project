#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class TPSWARSURVIVE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance(); //생성자(레벨에 해당 클래스에 있을때 호출하는 함수)

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

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool isAim = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FRotator AimRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UAnimSequence* PlayerAnimSequence;

//protected:
//	UPROPERTY(BlueprintReadOnly, Category = "Animation")
//	float Speed;
//
//	UPROPERTY(BlueprintReadOnly, Category = "Animation")
//	float Pitch;
//
//	UPROPERTY(BlueprintReadOnly, Category = "Animation")
//	float Direction;
//
//protected:
//	virtual void NativeInitializeAnimation() override; // 애니메이션이 생성되면 호출 함수
//
//	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // 프레임마다 호출 함수
};
