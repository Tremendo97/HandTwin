// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandTwin.generated.h"

//forward declaration de la estructura
struct FPosiciones;

UCLASS()
class HAND2_API AHandTwin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandTwin();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable) 
	TArray<uint8> StructureToBytes(const FPosiciones& pos);
};
