
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonstseBase.generated.h"

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	None UMETA(DisplayName = "None"),
	Enemy UMETA(DisplayName = "Enemy"),
};

UCLASS()
class TPSWARSURVIVE_API AMonstseBase : public ACharacter
{
	GENERATED_BODY()
public:
	AMonstseBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterState")
	EMonsterType monsterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterState")
	float monsterHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterState")
	FVector MonsterSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterState")
	TMap<EMonsterType, USkeletalMesh*> MonsterMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterState")
	TMap<EMonsterType, TSubclassOf<UAnimInstance>> MonsterAnimBlueprints;

public:
	void InitalizeMeshs();
	void InitalizeAnimInstance();
	void SetMonster();
};
