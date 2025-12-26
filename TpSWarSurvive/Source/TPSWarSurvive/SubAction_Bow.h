#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "SubAction.h"
#include "SubAction_Bow.generated.h"

USTRUCT()
struct FAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TargetArmLength = 100;

	UPROPERTY(EditAnywhere)
	FVector SocketOffset = FVector(0, 30, 10);

	UPROPERTY(EditAnywhere)
	bool bEnableCameraLog;

	UPROPERTY(EditAnywhere)
	FVector CameraLocation;
};

UCLASS(Blueprintable)
class TPSWARSURVIVE_API USubAction_Bow : public USubAction
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Aiming")
	class UCurveVector* Curve;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	FAimData AimData;

	UPROPERTY(EditAnywhere, Category = "Aiming")
	float AimingSpeed = 200;

public:
	//USubAction_Bow();

public:
	//void BeginPlay(class ACharacter* InOwner, class AAttachment* InAttackment)

private:
	//UFUNCTION()
	//	void OnAiming(FVector Output);
		
private:
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

private:
	FTimeline Timeline;
};
