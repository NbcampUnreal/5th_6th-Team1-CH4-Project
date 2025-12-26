#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"
#include "Attachment_Bow.generated.h"

UCLASS()
class TPSWARSURVIVE_API AAttachment_Bow : public AAttachment
{
	GENERATED_BODY()
	
private:
	// Pitch 각 제한하기 위해
	UPROPERTY(EditDefaultsOnly, Category = "View")
	FVector2D ViewPitchRange = FVector2D(-40, +30);

private:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	class UPoseableMeshComponent* PoseableMesh;

public:
	AAttachment_Bow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	//void OnBeginEquip_Implementation() override;
	//void OnUnequip_Implementation() override;

private:
	FVector2D OriginViewPitchRange;
};
