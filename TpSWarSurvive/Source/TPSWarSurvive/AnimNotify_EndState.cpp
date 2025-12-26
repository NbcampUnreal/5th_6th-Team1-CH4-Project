#include "AnimNotify_EndState.h"
#include "ICharacter.h"

FString UAnimNotify_EndState::GetNotifyName_Implementation() const
{
	return "EndState";
}

void UAnimNotify_EndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		if (MeshComp->GetOwner())
		{
			IICharacter* character = Cast<IICharacter>(MeshComp->GetOwner());
			if (character)
			{
				switch (StateType)
				{
				case EStateType::Idle:
					break;
				case EStateType::BackStep:
					character->End_BackStep();
					break;
				case EStateType::Equip:
					break;
				case EStateType::Hitted:
					break;
				case EStateType::Dead:
					break;
				case EStateType::Action:
					break;
				case EStateType::Max:
					break;
				default:
					break;
				}
			}
		}
	}
}
