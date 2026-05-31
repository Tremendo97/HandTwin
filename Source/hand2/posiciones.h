#pragma once

#include "CoreMinimal.h"
#include "Dedos.h"
#include "posiciones.generated.h"

USTRUCT(BlueprintType)
struct FPosiciones
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float posIndice1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float posIndice2;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EDedos dedo;
};

