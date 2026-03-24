// Fill out your copyright notice in the Description page of Project Settings.

#include "FL_hand2.h"
#include "posiciones.h"



TArray<uint8> UFL_hand2::StructureToBytes(const FPosiciones& Struct){

    TArray<uint8> Bytes;
    Bytes.SetNumUninitialized(sizeof(FPosiciones));
    FMemory::Memcpy(Bytes.GetData(), &Struct, sizeof(FPosiciones));
    return Bytes;
}

bool UFL_hand2::EqualStructure(const FPosiciones& posActual, const FPosiciones& posAnterior){

    if (posAnterior.dedo == EDedos::Vacio) {
        return true;
    }

    if (&posActual.dedo == &posAnterior.dedo && &posActual.posIndice1 == &posAnterior.posIndice1 && &posActual.posIndice2 == &posAnterior.posIndice2) {
        return true;
    }
    return false;
}