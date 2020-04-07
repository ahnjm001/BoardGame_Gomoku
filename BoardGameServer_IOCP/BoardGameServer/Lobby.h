#pragma once
#include <vector>
#include <algorithm>

#include "packet.h"
#include "RoomManager.h"

#include "User.h"
#include "NewRingBuffer.h"

#include "CriticalSectionClass.h"

class Channel;

//=====================================================

//Lobby

//�Ѱ��� Channel�� �ϳ��� Lobby �ϳ�
//�κ� ������ ���ͷ� ������

//�� ���� ����Ʈ�� ������ 2���̹Ƿ� �ٷιٷ� ��� �������� �� ���� ����Ʈ�� �����ش�.

//�κ� ������ ����,���� �� MakeLobbyUserList() �Լ��� ȣ���� �κ� ������ ������ ��Ŷ�� ������ش�.
//	+ CriticalSection���� ���ÿ� ������ ������ ���� ����

//=====================================================

class Lobby
{
private:
	RoomManager				m_roomManager;

	vector<User>			m_vlobbyUserList;

	ParticipantsInfo*		m_participantsInfo;

	Channel*				m_channel;

	CriticalSectionClass	m_locker;

public:
	Lobby();
	~Lobby();

	void Init();
	//�κ� �����ο� ��ü�� ä�� ������
	void SendChatAll_Lobby(SendChatting* _packet);

	//�κ� ���� ����Ʈ ������
	void SendLobbyUserList(NewRingBuffer* _data, User* _user);
	//�� ����Ʈ ������
	void SendRoomList(NewRingBuffer* _data, User* _user, ReqRoomListData* _packet);

	void PushBackLobbyUser(User* _user);
	void EraseLobbyUser(User* _user);

	void MakeLobbyUserList();

	void SetChannelData(Channel* _channel) { m_channel = _channel; }

	Channel* getChannelClass() { return m_channel; }
	RoomManager* getRoomManager() { return &m_roomManager; }
};