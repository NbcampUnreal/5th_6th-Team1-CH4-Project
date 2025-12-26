#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontagesComponent.generated.h"

USTRUCT()
struct FMontageData
	: public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EStateType Type;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1; // Player ¼Óµµ

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSWARSURVIVE_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* DataTable;

public:	
	UCMontagesComponent();

protected:

	virtual void BeginPlay() override;

public:
	void PlayBackStepMode();

private:
	void PlayAnimMontage(EStateType InType);

private:
	class ACharacter* OwnerCharacter;
	FMontageData* Datas[(int32)EStateType::Max];

};
