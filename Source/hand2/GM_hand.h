// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "GM_hand.generated.h"

/**
 * 
 */
UCLASS()
class HAND2_API AGM_hand : public AGameModeBase
{
	GENERATED_BODY()
private:
	FSocket* ServerSocket;
	FSocket* ClientSocket;
	ISocketSubsystem* SocketSubsystem;

public:
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void createListenSocket();
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void createSendSocket();
	UFUNCTION(BlueprintCallable, Category = "Sockets")
	void closeAplication();
	
};
