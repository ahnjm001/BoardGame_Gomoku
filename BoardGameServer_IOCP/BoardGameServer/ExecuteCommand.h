#pragma once
#include "User.h"
#include "packet.h"

#include "SessionManager.h"
#include "Lobby.h"

//=====================================================

//ExecuteCommand

//�Ľ��� ��Ŷ�� �ش��ϴ� ������� �����ϱ� ���� Ŭ����
//Update�� Channel���� Thread�� ���� ��� ��� ������ üũ�ذ��ִ�.

//�� �Ʒ��� �Լ����� ���� ��Ŷ���� �Լ���

//=====================================================

class ExecuteCommand
{
private:
	SessionManager<User>*	m_sessionManager;
	Lobby*					m_lobby;

public:
	ExecuteCommand();
	~ExecuteCommand();

	void Init(Lobby* _lobby, SessionManager<User>* _sessionManager);

	void Update();

	void Test(User* _user, char* _packet);
	void RegisterUser(User* _user, char* _packet);
	void SendChat(User* _user, WORD _num, char* _packet);
	void CreatingRoom(User* _user, char* _packet);
	void ExittingRoom(User* _user);
	void JoiningRoom(User* _user, char* _packet);
	void ReadyCheck(User* _user, char* _packet);
	void ReqLobbyUserList(User* _user);
	void ReqRoomList(User* _user, char* _packet);
	void GomokuGridPacket(User* _user, char* _packet);
	void GomokuResult(User* _user, char* _packet);

	void SendRoomUserList(int _tempNum, User* _user, bool _isExitted);
};