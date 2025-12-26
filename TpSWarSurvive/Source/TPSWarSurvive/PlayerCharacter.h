#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CStateComponent.h"
#include "InputActionValue.h"
#include "ICharacter.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	None UMETA(DisplayName = "None"),
	BowWeapon UMETA(DisplayName = "Bow"),
	Matchlockgun UMETA(DisplayName = "Matchlockgun"),
};

UCLASS()
class TPSWARSURVIVE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Weapon", BlueprintReadOnly)
	EWeaponTypes CurrentHandWeapon = EWeaponTypes::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* BowComp;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* ArrowComp;
private:
	UPROPERTY(VisibleAnywhere)
	class UCMontagesComponent* Montages;

	UPROPERTY(VisibleAnywhere)
	class UCStateComponent* State;

#pragma region CharacterActionClass 
private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* BowChangeAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* GunChangeAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* AimAction;

#pragma endregion

	UPROPERTY(VisibleAnywhere, Category = "Input")
	float mouseSpeed = 30;

#pragma region CharacterActionFunction
private:
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void BowChange();
	void GunChange();
	void OnAim();
	void OffAim();
	void Fire();
#pragma endregion

public:
	APlayerCharacter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Arrow")
	void TestFunction();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class ACharacter* OwnerCharacter;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	UAnimSequence* BowAnim;

private:
	//TArray<class AArrow*> Arrows;

	//class AArrow* GetAttachedArrow();


};
