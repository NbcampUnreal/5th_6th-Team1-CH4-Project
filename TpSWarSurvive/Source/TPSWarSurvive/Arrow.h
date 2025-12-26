#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileHit, class AActor*, InCauser, class APlayerCharacter*,
	InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjecttleEndPlay, class AArrow*, InDestroyer);

UCLASS()
class TPSWARSURVIVE_API AArrow : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UProjectileMovementComponent* Projectile;

public:	
	// Sets default values for this actor's properties
	AArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Shoot(const FVector& InForward);

public:
	FProjectileHit OnHit;
	FProjecttleEndPlay OnEndPlay;

};
