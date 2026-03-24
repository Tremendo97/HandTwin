// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_hand2.generated.h"

/**
 * 
 */
UCLASS()
class HAND2_API UFL_hand2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static TArray<uint8> StructureToBytes(const FPosiciones& Struct);

	UFUNCTION(BlueprintCallable)
	static bool EqualStructure(const FPosiciones& Struct1, const FPosiciones& Struct2 );
};
