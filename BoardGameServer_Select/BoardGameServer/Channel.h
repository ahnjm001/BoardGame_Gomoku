#pragma once
#include "ThreadClass.h"

#include "SelectClass.h"

#include "Lobby.h"

/*
// new (new char)�� ������ �޸� p�� ���� �մϴ�.
#define SAFE_DELETE( p ) { if( p ) { delete ( p ); ( p ) = NULL; } }

// new (new char *) �� ������ �迭 p�� ���� �մϴ�.
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p ); ( p ) = NULL; } }
*/

//=====================================================

//Channel

//���ο��� SelectClass�� ������

//=====================================================

class Channel : public ThreadClass<Channel>
{
private:
	WSADATA				wsaData;
	SOCKET				listenSocket;
	SOCKADDR_IN			servAddr;

	SelectClass<Lobby>	selectClass;
	bool				isFull;
	bool				isEmpty;

	Lobby				lobby;

public:
	Channel();
	~Channel();

	bool Init(int _portNum);

	void LoopRun();

	bool GetIsFull() { return isFull; }
	bool GetIsEmpty() { return isEmpty; }

	SOCKET GetListenSocket() { return listenSocket; }

	SelectClass<Lobby>* GetSelectClass() { return &selectClass; }
};

