#include "Bow.h"
#include "Arrow.h"


// Sets default values
ABow::ABow()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABow::CreateArrow()
{
}

AArrow* ABow::GetattachedArrow()
{
	//for (AArrow* projectile : Arrows)
	//{

	//}

	return nullptr;
}

