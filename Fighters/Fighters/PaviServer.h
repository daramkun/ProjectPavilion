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
 * �ĺ� ����
 * �ĺ����� ��Ʈ��ũ �÷��� ���� ����
 * Pavi Server
 * Server only Pavilion Network Play
 * UDP�� �������ݷ� �����
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
 * �ĺ� Ŭ���̾�Ʈ
 * �ĺ����� ��Ʈ��ũ �÷��� ���� Ŭ���̾�Ʈ �����
 * Pavi Client
 * Client Adapter only Pavilion Network Play
 * UDP�� �������ݷ� �����
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