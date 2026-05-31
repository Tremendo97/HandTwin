#pragma once

#include "CoreMinimal.h"
#include "Dedos.generated.h"

UENUM(BlueprintType/*, meta = (StructPacking = 1)*/)
enum class EDedos : uint8
{
    Indice = 0,
    Corazon = 1,
    Anular = 2,
    Menique = 3,
    Pulgar = 4,
    Vacio = 5
};
