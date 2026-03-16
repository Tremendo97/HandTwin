// Fill out your copyright notice in the Description page of Project Settings.

#include "FL_hand2.h"
#include "posiciones.h"



TArray<uint8> UFL_hand2::StructureToBytes(const FPosiciones& Struct)
{
    TArray<uint8> Bytes;
    Bytes.SetNumUninitialized(sizeof(FPosiciones));
    FMemory::Memcpy(Bytes.GetData(), &Struct, sizeof(FPosiciones));
    return Bytes;
}