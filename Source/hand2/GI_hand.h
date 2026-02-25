// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Tickable.h"
#include "Containers/Ticker.h"
#include "GI_hand.generated.h"


/**
 * 
 */
UCLASS()
class HAND2_API UGI_hand : public UGameInstance
{
	GENERATED_BODY()
private:
	FSocket* ServerSocket;
	FSocket* ClientSocket;
	FSocket* CreadoEnEjecucion;//este seria el socket cliente creado en el lado del servidor, cuando se acepta la conexion.
	ISocketSubsystem* SocketSubsystem;

public:
	//servidor
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void createListenSocket();
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void aceptarConexion();

	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void serverRecibirNumero();


	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void serverSendNumero();

	//cliente
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void createClientSocket(FString ipServer);

	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void clientSendNumber();

	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void clientRecibirNumero();

	//se ejecuta cuando se cierra la aplicacion para cerrar los sockets
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void closeAplication();

	//saber si es cliente o servidor
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	bool isServer();

	UFUNCTION(BlueprintCallable, Category = "Sockets")
	bool isClient();
};
