// Fill out your copyright notice in the Description page of Project Settings.

#include "FL_hand2.h"
#include "posiciones.h"
#include "Windows/WindowsHWrapper.h"
#include <fileapi.h>
#include <SetupAPI.h>
#include <devguid.h>



TArray<uint8> UFL_hand2::StructureToBytes(const FPosiciones& Struct){

    TArray<uint8> Bytes;
    Bytes.SetNumUninitialized(sizeof(FPosiciones));
    FMemory::Memcpy(Bytes.GetData(), &Struct, sizeof(FPosiciones));
    return Bytes;
}

bool UFL_hand2::EqualStructure(const FPosiciones& posActual, const FPosiciones& posAnterior){

    //UE_LOG(LogTemp, TEXT("valor1: %.32f   valor2: %.32f"), posActual.posIndice1, posAnterior.posIndice1);
    //, FColor::Cyan
    if (posAnterior.dedo == EDedos::Vacio) {
        return false;
    }

    if (posActual.dedo == posAnterior.dedo && posActual.articulacion1 == posAnterior.articulacion1 && posActual.articulacion2 == posAnterior.articulacion2) {
        
        return true;
    }
    return false;
}

TMap<int32, FString> UFL_hand2::getAvailablePorts()
{
    TMap<int32, FString> portList;

    //devuelve los dispositivos USB que hay conectados al ordenador.
    HANDLE devs = SetupDiGetClassDevs(
        (LPGUID)&GUID_DEVCLASS_PORTS,
        0,
        0,
        DIGCF_PRESENT
    );

    //señalara a cada uno de los dispositivos en el bucle for.
    SP_DEVINFO_DATA devInfo;
    devInfo.cbSize = sizeof(SP_DEVINFO_DATA);

    //recorremos los dispositivos encontrados
    for (DWORD i = 0; SetupDiEnumDeviceInfo(devs, i, &devInfo); i++) {
        //guarda el puerto en el que se encuentra el dispositivo.
        int32 portNumber = 0;
        //guarada el hardaware id del dispositivo.
        TCHAR hwid[256];
        
        //obtenemos el hardware id y el dispositivo.
        SetupDiGetDeviceRegistryProperty(
            devs,
            &devInfo,
            SPDRP_HARDWAREID,
            0,
            (PBYTE)hwid,
            sizeof(hwid),
            0);

        //obtenemos la hKey del dispoistivo
        HKEY hKey = SetupDiOpenDevRegKey(
            devs,
            &devInfo,
            DICS_FLAG_GLOBAL,
            0,
            DIREG_DEV,
            KEY_READ
        );

        //comprobamos la validez de la hKey
        if (hKey != INVALID_HANDLE_VALUE) {

            //guarada el puerto en el que esta el dispositivo
            TCHAR portName[256];
            DWORD size = sizeof(portName);
            DWORD type = 0;

            //obtenemos el puerto en el que esta alojado
            if (RegQueryValueEx(
                hKey,
                TEXT("PortName"),
                NULL,
                &type,
                (LPBYTE)portName,
                &size) == ERROR_SUCCESS) {

                
                swscanf(portName, L"COM%d", &portNumber);
                portList.Add(portNumber, "no Arduino");
            }

            RegCloseKey(hKey);

        }
        else {
            UE_LOG(LogTemp, Error, TEXT("el hKey del dispositivoc on hardware id : %s"), hwid);
        }

        //comprobamos si es un arduino real
        if (wcsstr(hwid, TEXT("VID_2341")) || wcsstr(hwid, TEXT("VID_2A03")) ) {

            //guardara el nombre del arduino.
            TCHAR name[256];

            //obtenemos el nombre del arduino.
            SetupDiGetDeviceRegistryProperty(
                devs,
                &devInfo,
                SPDRP_FRIENDLYNAME,
                0,
                (PBYTE)name,
                sizeof(name),
                0);

            portList[portNumber] = name;
        }
    }

    return portList;
}

double UFL_hand2::getTiempoPreciso() {
    return FPlatformTime::Seconds();
}