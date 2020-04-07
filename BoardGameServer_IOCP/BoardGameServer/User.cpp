#include "User.h"

User::User()
{
	
}

User::~User()
{
	
}

//������Ʈ Ǯ�� �ٽ� ������ �ʱ�ȭ�Ҷ� ����� �Լ�
void User::Reset()
{
	m_recvBuffer->Reset();
	m_sendBuffer->Reset();

	m_info = {};

	m_recvBytes = 0;
	m_flags = 0;
	m_sendBytes = 0;
}

void User::OnConnect(SOCKET _socket, int _num, int _portNum)
{
	m_info.userID = _num;
	m_info.socket = _socket;
	m_info.roomNum = 0;

	IOCPCLASS->AddSocket(_socket, (DWORD)this);

	m_isConnected = true;

	//==========================================================

	UserData* data = new UserData();
	data->cmd = 90;
	data->userID = _num;
	data->socket = _socket;
	data->roomNum = 0;
	data->size = sizeof(UserData);

	//sendBuffer->Write()
	Send(reinterpret_cast<char*>(data), sizeof(UserData));

	//send(_socket, (char*)data, sizeof(UserData), 0);

	printf("[client socket : %d / count : %d / portNum : %d]\n", _socket, _num, _portNum);

	Recv();
}

//���� ��������(������Ʈ Ǯ�� �ٽ� ��ȯ�� ��)
void User::Disconnect()
{
	//�ʱ�ȭ
	this->Reset();
}

void User::SetName(UserData* _data)
{
	strcpy(m_info.name, _data->name);
	m_info.nameSize = strlen(m_info.name);
}

void User::SetReady(IsReady* _data)
{
	m_info.isReady = _data->isReady;
}