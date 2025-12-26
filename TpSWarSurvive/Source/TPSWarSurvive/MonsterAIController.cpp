#include "MonsterAIController.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AMonsterAIController::AMonsterAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreedComponent"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_Monster.BT_Monster'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_Monster.BB_Monster'"));

	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("BT.Succeeded"));
	}

	if (BB.Succeeded())
	{
		BlackboardData = BB.Object;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("BB.Succeeded"));

	}
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);

		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("TargetActor"), playerPawn->GetActorLocation());
	}
}

