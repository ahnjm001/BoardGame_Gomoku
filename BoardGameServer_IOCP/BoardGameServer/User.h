#pragma once
#include "Session.h"
//=====================================================

//User

//Session ��ӹ޾� App�ܿ��� �� Ŭ����

//=====================================================

class User : public Session
{
private:


public:
	User();
	~User();

	void Reset();

	void SetName(UserData* _data);
	void SetReady(IsReady* _data);

	void OnConnect(SOCKET _socket, int _num, int _portNum);
	void Disconnect();
};

