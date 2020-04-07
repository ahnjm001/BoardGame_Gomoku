#include "Channel.h"

Channel::Channel()
{
}

Channel::~Channel()
{
}

bool Channel::Init(int _portNum)
{
	m_lobby.Init();
	//��ȣ������ �Լ���
	m_lobby.SetChannelData(this);

	m_sessionManager.Init();

	//�ϴ� ������ ���� ��ɵ� ���� ����� listen�� accpet�� ��������
	if (!m_listenClass.Init(&m_sessionManager, _portNum)) return false;

	//���� ��Ŷó�� �κ� ����
	m_executeCommand.Init(&m_lobby, &m_sessionManager);

	ThreadClass<Channel>::Start(this);

	return  true;
}

//ä���� ������
void Channel::LoopRun()
{
	while (1)
	{
		m_executeCommand.Update();

		Sleep(1);
	}
}