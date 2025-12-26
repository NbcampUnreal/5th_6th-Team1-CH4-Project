#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubAction.generated.h"


UCLASS(Abstract)//객체화하지 않을 경우, Abstract 명시
class TPSWARSURVIVE_API USubAction : public UObject
{
	GENERATED_BODY()
	
public:
	USubAction();
};
