#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <process.h>

#include <map>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#include "packet.h"

#include "ObjectPool.h"
#include "ThreadClass.h"

#include "User.h"

#define MAX 100

using namespace std;

//=====================================================

//SelectClass

//Server���� �޾ƿ� Lobby �����͸� Session���� ����(�ڼ��Ѱ� Server.h�� �����)

//Session�� Map���� ������ ���� -> ���� �񵿱� ��� �Ŀ� Map �� ������ ������ Select���� ����ϹǷ� Select���� Map���� Session�� �����ص���.

//=====================================================

template<typename T>
class SelectClass : public ThreadClass<SelectClass<T>>, public ObjectPool<User>
{
private:
	T* t;

	//============================================

	//Server.h���� ������ ����
	SOCKET			ChannelListenSocket;

	fd_set			fdSocketInfors;		// socket ������ �����ϰ� �ִ� ����ü
	fd_set			fdReads;			// ��ȭ�� �о�� ����ü
	int				iRet;
	SOCKET			sockClient, sockTemp;
	SOCKADDR_IN		addrClient;

	int				portNum;

	//============================================

	//Session�� ������ Select���� ���� (������ ���� ����)
	typedef map<SOCKET, User*>					mSessionList;
	typedef map<SOCKET, User*>::iterator		mSessionIter;

	mSessionList				mSession;

	int							count;

	//============================================

	User* tempSession;

	//============================================

	bool isFull;

public:
	SelectClass()
	{

	}

	~SelectClass()
	{

	}

	bool GetIsFull() { return isFull; }
	int GetSessionSize() { return mSession.size(); }

	void Init(SOCKET _listenSocket, int _portNum, T* _t)
	{
		ChannelListenSocket = _listenSocket;
		portNum = _portNum;

		FD_ZERO(&fdSocketInfors);
		FD_SET(ChannelListenSocket, &fdSocketInfors);

		t = _t;

		count = 0;
	}

	bool Blocking()
	{
		fdReads = fdSocketInfors;
		//blocking - ������ ������ �ְ� ���
		iRet = select(0, &fdReads, 0, 0, 0);

		if (iRet == SOCKET_ERROR) return false;
	}

	void ModifyingCheck()
	{
		for (u_int i = 0; i < fdSocketInfors.fd_count; i++)
		{
			sockTemp = fdSocketInfors.fd_array[i];

			//������ ���� �߿� ��ȭ�� �Ͼ ������ �ִ���
			if (FD_ISSET(sockTemp, &fdReads))
			{
				//Reads �� �Ͼ ������ ������ ��� accept
				if (sockTemp == ChannelListenSocket)
				{
					this->AcceptProcess();
				}
				else //client�� ��� recv ó��
				{
					this->RecvProcess();
				}
			}
		}
	}

	void AcceptProcess()
	{
		//Reads �� �Ͼ ������ ������ ��� accept
		int temp = sizeof(addrClient);
		sockClient = accept(ChannelListenSocket, (SOCKADDR*)&addrClient, &temp);

		if (sockClient == INVALID_SOCKET)
		{
			printf("Failed accept() \n");
		}

		this->AddSession(sockClient);

		FD_SET(sockClient, &fdSocketInfors);
	}

	void RecvProcess()
	{
		//client�� ��� recv ó��
		printf("[Recv Start]\n");

		//true -> ���� �����	
		if (this->FindSession(sockTemp)->Recv() == true)
		{
			//�ӽ� ����
			//�ӽ������� ���ؼ� �� ����
			//  -> ���� Recv�Ҷ����� �ӽ�������ϰ� �����ҋ��� ObjectPool�� �ݳ��ϱ� ���� �ӽ������Ѵ�.
			tempSession = this->FindSession(sockTemp);
			tempSession->Reset();

			//�ʿ��� ���� ��
			//�� ���� ���� �� ����
			//	-> ObjectPool�� ���� �ݳ��ϸ� map�� �ִ°� ��� ���� ���� ���� �ߴ�.
			DeleteSession(sockTemp);

			//ObjectPool�� �ݳ�
			ReturnObject(tempSession);
			tempSession = NULL;

			FD_CLR(sockTemp, &fdSocketInfors);
		}

		printf("[Recv End]\n");
		printf("================================================== \n");
	}

	void AddSession(SOCKET _socket)
	{
		//2019/10/17
		//������Ʈ Ǯ�� �ٲ� ����
		tempSession = PopObject();

		if (tempSession != NULL)
		{
			count++;
			tempSession->Init(t);
			tempSession->RegisterUser(_socket, count, portNum);

			mSession.insert(make_pair(_socket, tempSession));
		}

		tempSession = NULL;
	}

	User* FindSession(SOCKET _socket)
	{
		mSessionIter key = mSession.find(_socket);

		if (key != mSession.end())
		{
			return key->second;
		}

		return NULL;
	}

	void DeleteSession(SOCKET _socket)
	{
		mSessionIter key = mSession.find(_socket);

		if (key != mSession.end())
		{
			mSession.erase(_socket);

			count--;
		}
	}

	void IsFullCheck()
	{
		if (mSession.size() >= 100)
		{
			isFull = true;
		}
		else
		{
			isFull = false;
		}
	}

	void LoopRun()
	{
		while (1)
		{
			if (!this->Blocking())
			{
				break;
			}

			ModifyingCheck();

			IsFullCheck();
		}
	}
};