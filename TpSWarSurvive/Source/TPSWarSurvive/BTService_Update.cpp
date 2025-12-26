#include "BTService_Update.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_Update::UBTService_Update()
{
	NodeName = "UpdateLocation";
}

void UBTService_Update::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetActor"), playerPawn->GetActorLocation());
}
