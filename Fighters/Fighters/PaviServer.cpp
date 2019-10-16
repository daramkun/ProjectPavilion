#include "PaviServer.h"

bool PaviServer::OpenServer()
{
	WSAData data;
	//WSAStartup(MAKEWORD(2, 2), &data);
	//socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, NULL, WSA_FLAG_OVERLAPPED);
	//listen(socket, 1);

	return false;
}

void PaviServer::CloseServer()
{
	//closesocket(socket);
	//WSACleanup();
}

void PaviServer::Send()
{

}

void PaviServer::Receive()
{

}