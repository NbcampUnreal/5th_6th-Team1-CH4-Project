#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attachment.generated.h"

UCLASS()
class TPSWARSURVIVE_API AAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USceneComponent* Root;

public:	
	AAttachment();

protected:
	virtual void BeginPlay() override;

public:
	//UFUNCTION(BlueprintNativeEvent)
	//void OnBeginEquip();
	//virtual void OnBeginEquip_Implementation() {}

	//UFUNCTION(BlueprintNativeEvent)
	//void OnUnequip();
	//virtual void OnUnequip_Implementation() {}

public: 
	void OnCollisions();
	void OffCollision();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	TArray<class UShapeComponent*> Collisions;
};
