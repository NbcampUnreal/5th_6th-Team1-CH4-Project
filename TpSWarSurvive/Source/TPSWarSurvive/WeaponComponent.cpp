#include "WeaponComponent.h"
#include "CStateComponent.h"
#include "GameFramework/Character.h"
#include "WeaponAsset.h"
#include "Attachment.h"
#include "CEquipment.h"

UWeaponComponent::UWeaponComponent()
{

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		//if (!!DataAssets[i]) //DataAssets[i]이 있다면(=무기가 할당되어 있다면)
		//	DataAssets[i]->BeginPlay();
	}
}




