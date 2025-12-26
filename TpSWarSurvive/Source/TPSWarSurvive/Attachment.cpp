#include "Attachment.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

AAttachment::AAttachment()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AAttachment::BeginPlay()
{
	// BP에서 BeginPlay이 먼저 호출되면 터진다.
	// 먼저 세팅 후 부모를 불러줘야한다.
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Super::BeginPlay();
	
}

//void AAttachment::OnBeginEquip()
//{
//}
//
//void AAttachment::OnUnequip()
//{
//}

void AAttachment::OnCollisions()
{
}

void AAttachment::OffCollision()
{
}



