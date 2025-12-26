#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponAsset.generated.h"


UCLASS()
class TPSWARSURVIVE_API UWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAttachment> AttachmentClass;

public:
	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }

public:
	UWeaponAsset();

	void BeginPlay(class AAttachment* InOwner);

private:

	UPROPERTY()
	class AAttachment* Attachment;
};
