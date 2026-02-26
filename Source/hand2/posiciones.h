// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "posiciones.generated.h"

USTRUCT(BlueprintType)
struct FPosiciones
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float posIndice1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float posIndice2;
};
