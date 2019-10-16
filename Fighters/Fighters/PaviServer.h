#pragma once

#include <winsock2.h>

enum SENDTYPE
{
	NO_TYPE = 0,
	CHAR_MOVE = 1,
	CHAR_ACTION = 2,
	CHAR_CRASHED = 3,
};

/*////////////////////////////////////////////////////////
 * 파비 서버
 * 파빌리언 네트워크 플레이 전용 서버
 * Pavi Server
 * Server only Pavilion Network Play
 * UDP를 프로토콜로 사용함
 * Using protocol is UDP
////////////////////////////////////////////////////////*/
class PaviServer
{
private:
	SOCKET socket;
public:
	bool OpenServer();
	void CloseServer();

	void Send();
	void Receive();
};

/*////////////////////////////////////////////////////////
 * 파비 클라이언트
 * 파빌리언 네트워크 플레이 전용 클라이언트 어댑터
 * Pavi Client
 * Client Adapter only Pavilion Network Play
 * UDP를 프로토콜로 사용함
 * Using protocol is UDP
////////////////////////////////////////////////////////*/
class PaviClient
{
public:
	bool ConnServer();
	void CloseClient();
	
	void Send();
	void Receive();
};