#include "CMontagesComponent.h"
#include "GameFramework/Character.h"

UCMontagesComponent::UCMontagesComponent()
{

}

void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "DataTable is not selected");

		return;
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				continue;
			}
		}
	}
}

void UCMontagesComponent::PlayBackStepMode()
{
	PlayAnimMontage(EStateType::BackStep);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	if (OwnerCharacter)
	{
		FMontageData* data = Datas[(int32)InType];

		if (data == nullptr || data->Montage == nullptr)
		{
			GLog->Log(ELogVerbosity::Error, "None montages data");

			return;
		}

		OwnerCharacter->PlayAnimMontage(data->Montage, data->PlayRate);
		//data의 몽타주를 PlayRate속도로 OwnerCharacter에 적용하여 재생
	}
}


