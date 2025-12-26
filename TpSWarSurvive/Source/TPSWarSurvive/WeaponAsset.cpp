#include "WeaponAsset.h"
#include "Attachment.h"
#include "GameFramework/Character.h"

UWeaponAsset::UWeaponAsset()
{
	AttachmentClass = AAttachment::StaticClass();
}

void UWeaponAsset::BeginPlay(AAttachment* InOwner)
{
	//if(!!Equi)

	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<AAttachment>(AttachmentClass, params);
	}
}
