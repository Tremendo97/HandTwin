// Fill out your copyright notice in the Description page of Project Settings.


#include "HandTwin.h"
#include "posiciones.h"

// Sets default values
AHandTwin::AHandTwin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHandTwin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandTwin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<uint8> AHandTwin::StructureToBytes(const FPosiciones& pos)
{
    TArray<uint8> Bytes;
    Bytes.SetNumUninitialized(sizeof(FPosiciones));
    FMemory::Memcpy(Bytes.GetData(), &pos, sizeof(FPosiciones));
    return Bytes;
}

