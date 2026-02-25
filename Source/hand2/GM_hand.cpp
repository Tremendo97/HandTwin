// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_hand.h"
#include <Interfaces/IPv4/IPv4Endpoint.h>

void AGM_hand::createListenSocket() {
	if (!SocketSubsystem) {
		SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	}

	ServerSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), FString(TEXT("estoe es una descripcion de mi socket que se crea en GM_hand")), false);


	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress);
	FIPv4Endpoint Endpoint(IPAddress, 50000);

	ServerSocket->Bind(*Endpoint.ToInternetAddr());

	ServerSocket->Listen(1);
	ServerSocket->Accept(FString(TEXT("esperoa a aceptar un socket")));
}

void AGM_hand::createSendSocket() {
	if (!SocketSubsystem) {
		SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	}

	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress);
	FIPv4Endpoint Endpoint(IPAddress, 50000);

	ClientSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), FString(TEXT("estoe es una descripcion de mi socket que se crea en GM_hand")), false);
	ClientSocket->Connect(*Endpoint.ToInternetAddr());
}

void AGM_hand::closeAplication() {
	if (!ServerSocket) {
		SocketSubsystem->DestroySocket(ServerSocket);
	}
	if (!ClientSocket) {
		SocketSubsystem->DestroySocket(ClientSocket);
	}
}