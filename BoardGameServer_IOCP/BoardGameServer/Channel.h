#pragma once
#include "ThreadClass.h"

#include "ListenClass.h"

#include "Lobby.h"

#include "User.h"
#include "SessionManager.h"

#include "ExecuteCommand.h"

//=====================================================

//Channel

//Channel �ϳ��� ListenClass, SessionManager, Lobby�� ����������.
//ListenClass���� Accept�޴� ��.
//ExecuteCommand Ŭ������ �̿��� LoopRun���� �ش� ä���� �����鿡�� ��Ŷ ó�� ��

//=====================================================

class Channel : public ThreadClass<Channel>
{
private:
	ListenClass				m_listenClass;

	Lobby					m_lobby;
	SessionManager<User>	m_sessionManager;

	ExecuteCommand			m_executeCommand;

public:
	Channel();
	~Channel();

	bool Init(int _portNum);

	void LoopRun();

	Lobby	GetLobby() { return m_lobby; }
	SessionManager<User> GetSessionManager() { return m_sessionManager; }
};