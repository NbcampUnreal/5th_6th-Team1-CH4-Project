#include "Attachment_Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

AAttachment_Bow::AAttachment_Bow()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> BowMesh
	(TEXT(""));
	if(BowMesh.Succeeded())
	{
		SkeletalMesh->SetSkeletalMesh(BowMesh.Object);
		SkeletalMesh->SetCollisionProfileName("NoCollision");
	}
}

void AAttachment_Bow::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMesh->SetVisibility(false);

	PoseableMesh->SetSkeletalMesh(SkeletalMesh->SkeletalMesh); // 숨겨놓은 SkeLMesh를 넣어준다.
	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletalMesh); // 우선 한번 캡쳐해놓기

}

void AAttachment_Bow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 캡쳐를 계속 진행한다.
	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletalMesh);
}

//void AAttachment_Bow::OnBeginEquip_Implementation()
//{
//	Super::OnBeginEquip_Implementation();
//
//	//APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
//	//if (!!controller)
//	//{
//	//	// Bow 착용시 상하 움직임 제한 걸ㅇ어준다.
//	//	//OriginViewPitchRange.X = controller->Pla
//	//}
//
//}
//
//void AAttachment_Bow::OnUnequip_Implementation()
//{
//	Super::OnUnequip_Implementation();
//}
