#include "GI_hand.h"
#include <Interfaces/IPv4/IPv4Endpoint.h>
#include "IPAddress.h"

void UGI_hand::createListenSocket() {
	if (!SocketSubsystem) {
		SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	}

	ServerSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), FString(TEXT("estoe es una descripcion de mi socket que se crea en GM_hand")), false);
	//hace que no sea bloqueante
	ServerSocket->SetNonBlocking(true);
	

	uint32 RawIP;
	SocketSubsystem->GetLocalBindAddr(*GLog)->GetIp(RawIP);

	//FIPv4Address solo guarda la IP
	FIPv4Address IPAddress(RawIP);
	
	//esta linea hacia un loopback para crear los shokets de forma local
	//FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress);

	FIPv4Endpoint Endpoint(IPAddress, 50000);

	//FInternetAddr guarda tanto IP como puerto
	ServerSocket->Bind(*Endpoint.ToInternetAddr());
	

	//TSharedRef< FInternetAddr > direccion = SocketSubsystem->GetLocalBindAddr(*GLog);

	ServerSocket->Listen(1);
}

void UGI_hand::createClientSocket(FString ipServer) {
	if (!SocketSubsystem) {
		SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	}

	FIPv4Address IPAddress;
	FIPv4Address::Parse(ipServer, IPAddress);
	FIPv4Endpoint Endpoint(IPAddress, 50000);

	ClientSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), FString(TEXT("este socket se conecta al PLC")), false);

	//hace que no sea bloqueante
	ClientSocket->SetNonBlocking(true);

	ClientSocket->Connect(*Endpoint.ToInternetAddr());
}

void UGI_hand::closeAplication() {
	//comprobamos si ambos sockets estan inicializados, si es el caso los cerramos y los destruimos
	if (ServerSocket) {
		ServerSocket->Close();
		SocketSubsystem->DestroySocket(ServerSocket);
	}
	if (ClientSocket) {
		ClientSocket->Close();
		SocketSubsystem->DestroySocket(ClientSocket);
	}
}

void UGI_hand::clientSendNumber() {
	int32 mensaje = 12345;
	int32 tamanoReal = sizeof(mensaje);
	int32 tamanoEnviado = 0;

	bool enviado = ClientSocket->Send((uint8*)&mensaje,tamanoReal,tamanoEnviado);

	if (enviado) {
		UE_LOG(LogTemp, Warning, TEXT("Cliente: tamano real=%d tamano enviado=%d"), tamanoReal, tamanoEnviado);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Cliente: no se ha enviado"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Cliente: acabo enviar"));
}

void UGI_hand::aceptarConexion() {
	if (!ServerSocket) {
		return;
	}
	bool conexionPendiente=false;
	ServerSocket->HasPendingConnection(conexionPendiente);

	if (conexionPendiente) {
		CreadoEnEjecucion = ServerSocket->Accept(FString(TEXT("cliente")));
	}
}

void UGI_hand::serverRecibirNumero() {
	bool rec= false;

	int32 MensajeRecibido = 0;
	int32 TamanoRecibido = 0;

	if (CreadoEnEjecucion) {
		rec = CreadoEnEjecucion->Recv((uint8*)&MensajeRecibido, sizeof(MensajeRecibido), TamanoRecibido, ESocketReceiveFlags::None);
	}
	if (rec) {
		UE_LOG(LogTemp, Warning, TEXT("Server: Se ha recibido: %d"), MensajeRecibido);
		return;
	}
}

void UGI_hand::serverSendNumero() {
	int32 mensaje = 12345;
	int32 tamanoReal = sizeof(mensaje);
	int32 tamanoEnviado = 0;

	bool enviado = CreadoEnEjecucion->Send((uint8*)&mensaje, tamanoReal, tamanoEnviado);

	if (enviado) {
		UE_LOG(LogTemp, Warning, TEXT("Server: tamano real=%d tamano enviado=%d"), tamanoReal, tamanoEnviado);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Server: no se ha enviado"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Server: acabo enviar"));
}

void UGI_hand::clientRecibirNumero() {
	bool rec = false;

	int32 MensajeRecibido = 0;
	int32 TamanoRecibido = 0;

	if (ClientSocket) {
		rec = ClientSocket->Recv((uint8*)&MensajeRecibido, sizeof(MensajeRecibido), TamanoRecibido, ESocketReceiveFlags::None);
	}
	if (rec) {
		UE_LOG(LogTemp, Warning, TEXT("Cliente: Se ha recibido: %d"), MensajeRecibido);
		return;
	}
}

bool UGI_hand::isServer() {
	if (ServerSocket) {
		return true;
	}
	else{
		return false;
	}
}

bool UGI_hand::isClient() {
	if (ClientSocket) {
		return true;
	}
	else {
		return false;
	}
}
