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

	UFUNCTION(BlueprintCallable, meta = (ReturnDisplayName = "Equal"))
	static bool EqualStructure(UPARAM(DisplayName="Posicion actual") const FPosiciones& Struct1, UPARAM(DisplayName = "Posicion anterior") const FPosiciones& Struct2);

    UFUNCTION(BlueprintCallable)
    static TMap<int32, FString> getAvailablePorts();

	UFUNCTION(BlueprintCallable, Category = "Tiempo")
	static double getTiempoPreciso();
};




