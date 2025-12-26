#include "MonstseBase.h"
#include "MonsterAIController.h"

AMonstseBase::AMonstseBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	InitalizeMeshs();
	InitalizeAnimInstance();
}

void AMonstseBase::BeginPlay()
{
	Super::BeginPlay();
	SetMonster();
}

void AMonstseBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonstseBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonstseBase::InitalizeMeshs()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		DefalutMonsterMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Pirate/Mesh_UE5/Full/SKM_Pirate_Full_01.SKM_Pirate_Full_01'"));

	if (DefalutMonsterMesh.Succeeded())
	{
		MonsterMeshes.Add(EMonsterType::Enemy, DefalutMonsterMesh.Object);
	}
}

void AMonstseBase::InitalizeAnimInstance()
{
	static ConstructorHelpers::FClassFinder<UAnimInstance> 
		DefalutMonsterAni(TEXT("/Game/Blueprints/Monster/ABP_Monster.ABP_Monster_C"));
	if (DefalutMonsterAni.Class)
	{
		MonsterAnimBlueprints.Add(EMonsterType::Enemy, DefalutMonsterAni.Class);
	}

}

void AMonstseBase::SetMonster()
{
	monsterType = EMonsterType::Enemy;

	if (monsterType == EMonsterType::Enemy)
	{
		//if (MonsterMeshes.Contains(EMonsterType::Enemy) && MonsterAnimBlueprints.Contains(EMonsterType::Enemy))
		//{
		//	GetMesh()->SetSkeletalMesh(MonsterMeshes[EMonsterType::Enemy]);
		//	//GetMesh()->SetAnimInstanceClass(MonsterAnimBlueprints[EMonsterType::None]);
		//	monsterHP = 100;
		//	MonsterSize = FVector(1.2f, 1.2f, 1.2f);
		//}

		if (MonsterMeshes.Contains(EMonsterType::Enemy) && MonsterAnimBlueprints.Contains(EMonsterType::Enemy))
		{
			GetMesh()->SetSkeletalMesh(MonsterMeshes[EMonsterType::Enemy]);
			GetMesh()->SetAnimInstanceClass(MonsterAnimBlueprints[EMonsterType::Enemy]);
			monsterHP = 100;
			MonsterSize = FVector(1.0f, 1.0f, 1.0f);
		}
	}
	//GetMesh()->SetSkeletalMesh(MonsterMeshes[EMonsterType::Enemy]);
	//MonsterSize = FVector(1.0f, 1.0f, 1.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	SetActorScale3D(MonsterSize);
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

