#include "RoomManager.h"
#include "User.h"

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::Init()
{
	memset(m_roomStruct, NULL, ROOMMAX * sizeof(RoomStruct<User>*));

	m_roomCount = 0;

	ObjectPool<RoomStruct<User>>::ObjectPool(50);

	//�̸� ���� �޼��� �����α�
	char tempCharArray[255] = "������ ���� �������� �ʽ��ϴ�. ���ΰ�ħ ���ּ���.";
	m_sendNoRoom = new SendChatting();

	m_sendNoRoom->cmd = 91;
	strncpy(m_sendNoRoom->name, "System",sizeof("System"));
	m_sendNoRoom->nameSize = sizeof(m_sendNoRoom->name);
	strcpy(m_sendNoRoom->message, tempCharArray);
	m_sendNoRoom->size = sizeof(m_sendNoRoom);

	/*m_roomListInfo_1 = new CreatedRoomList();
	m_roomListInfo_1->cmd = 96;
	m_roomListInfo_1->count = 0;
	m_roomListInfo_1->arraySize = m_roomListInfo_1->count * sizeof(SendingRoomStruct);
	m_roomListInfo_1->size = 20 + m_roomListInfo_1->arraySize;

	m_roomListInfo_2 = new CreatedRoomList();
	m_roomListInfo_2->cmd = 96;
	m_roomListInfo_2->count = 0;
	m_roomListInfo_2->arraySize = m_roomListInfo_2->count * sizeof(SendingRoomStruct);
	m_roomListInfo_2->size = 20 + m_roomListInfo_2->arraySize;

	m_roomListInfo_3 = new CreatedRoomList();
	m_roomListInfo_3->cmd = 96;
	m_roomListInfo_3->count = 0;
	m_roomListInfo_3->arraySize = m_roomListInfo_3->count * sizeof(SendingRoomStruct);
	m_roomListInfo_3->size = 20 + m_roomListInfo_3->arraySize;

	m_roomListInfo_4 = new CreatedRoomList();
	m_roomListInfo_4->cmd = 96;
	m_roomListInfo_4->count = 0;
	m_roomListInfo_4->arraySize = m_roomListInfo_4->count * sizeof(SendingRoomStruct);
	m_roomListInfo_4->size = 20 + m_roomListInfo_4->arraySize;

	m_roomListInfo_5 = new CreatedRoomList();
	m_roomListInfo_5->cmd = 96;
	m_roomListInfo_5->count = 0;
	m_roomListInfo_5->arraySize = m_roomListInfo_5->count * sizeof(SendingRoomStruct);
	m_roomListInfo_5->size = 20 + m_roomListInfo_5->arraySize;*/
}

RoomStruct<User>* RoomManager::FindRoom(int _roomNum)
{
	for (int i = 0; i < m_roomCount; i++)
	{
		if (m_roomStruct[i]->roomInfo.index == _roomNum)
		{
			return m_roomStruct[i];
		}
	}

	return NULL;
}

//�� ���� ä�� ����
void RoomManager::SendChattAll_Room(int _roomNum, SendChatting* _packet)
{
	RoomStruct<User>* tempRoom = FindRoom(_roomNum);

	if (tempRoom == NULL) return;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		tempRoom->user[i]->Send(reinterpret_cast<char*>(_packet), sizeof(SendChatting));
	}
}

//�� �����ο� ���� �Ѹ���
void RoomManager::SendRoomUserList(NewRingBuffer* _data, User* _user)
{
	ParticipantsInfo* partiInfo = (ParticipantsInfo*)_data->GetWritePoint();
	RoomStruct<User>* tempRoom = FindRoom(_user->GetSessionInfo().roomNum);

	if (tempRoom == NULL) return;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		partiInfo->BelongInfos[i] = tempRoom->user[i]->GetSessionInfo();
	}

	partiInfo->cmd = 95;
	partiInfo->count = tempRoom->roomInfo.count;
	partiInfo->arraySize = partiInfo->count * sizeof(userInformation);
	partiInfo->size = 20 + partiInfo->arraySize;

	_user->Send(reinterpret_cast<char*>(partiInfo), partiInfo->size);
}

void RoomManager::SendRoomUserListToOther(NewRingBuffer* _data, int _roomNum)
{
	if (_roomNum <= 0) return;

	ParticipantsInfo* partiInfo = (ParticipantsInfo*)_data->GetWritePoint();
	RoomStruct<User>* tempRoom = FindRoom(_roomNum);

	if (tempRoom == NULL) return;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		partiInfo->BelongInfos[i] = tempRoom->user[i]->GetSessionInfo();
	}

	partiInfo->cmd = 95;
	partiInfo->count = tempRoom->roomInfo.count;
	partiInfo->arraySize = partiInfo->count * sizeof(userInformation);
	partiInfo->size = 20 + partiInfo->arraySize;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		//_data->Write(partiInfo->size);

		tempRoom->user[i]->Send(reinterpret_cast<char*>(partiInfo), partiInfo->size);
	}
}

//�� �� �ٸ� �����ο��鿡�� �����ο� ���� �Ѹ���
void RoomManager::SendRoomUserListToOther(NewRingBuffer* _data, User* _user)
{
	if (_user->GetSessionInfo().roomNum <= 0) return;

	ParticipantsInfo* partiInfo = (ParticipantsInfo*)_data->GetWritePoint();
	RoomStruct<User>* tempRoom = FindRoom(_user->GetSessionInfo().roomNum);

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		partiInfo->BelongInfos[i] = tempRoom->user[i]->GetSessionInfo();
	}

	partiInfo->cmd = 95;
	partiInfo->count = tempRoom->roomInfo.count;
	partiInfo->arraySize = partiInfo->count * sizeof(userInformation);
	partiInfo->size = 20 + partiInfo->arraySize;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (tempRoom->user[i]->GetSessionInfo().userID != _user->GetSessionInfo().userID)
		{
			//_data->Write(partiInfo->size);

			tempRoom->user[i]->Send(reinterpret_cast<char*>(partiInfo), partiInfo->size);
		}
	}
}

void RoomManager::RoomUserUpdate(User* _user)
{
	RoomStruct<User>* tempRoom = FindRoom(_user->GetSessionInfo().roomNum);

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (tempRoom->user[i]->GetSessionInfo().userID ==
			_user->GetSessionInfo().userID)
		{
			tempRoom->user[i]->SetIsReady(_user->GetSessionInfo().isReady);

			if (this->ReadyCheck(tempRoom))
			{
				//�÷��̾ ���� Ready�� �����Ƿ� ���� �÷��� ������ ��ȯ
				tempRoom->roomInfo.isPlaying = true;
			}
		}
	}
}

bool RoomManager::CreateRoom(NewRingBuffer* _data, User* _user)
{
	if (m_roomCount >= ROOMMAX)
	{
		printf("[�� ���� ���� ������ �ɸ�] \n");

		return false;
	}

	m_locker.EnterLock();

	for (int i = 0; i < ROOMMAX; i++)
	{
		if (m_roomStruct[i] == NULL)
		{
			m_roomStruct[i] = PopObject();

			m_roomCount++;

			//�߰��� �� �� ��ȣ�� ������ �Ҵ�
			if (m_roomNum.size() > 0)
			{
				m_roomStruct[i]->roomInfo.index = m_roomNum[0];
				m_roomNum.erase(m_roomNum.begin());
			}
			//�ƴϸ� ��� ��
			else
			{
				m_roomStruct[i]->roomInfo.index = i + 1;
			}

			m_roomStruct[i]->roomInfo.count = 1;
			m_roomStruct[i]->roomInfo.complement = 2;
			m_roomStruct[i]->user[0] = _user;
			m_roomStruct[i]->roomInfo.isPlaying = false;

			UserData* data = (UserData*)_data->GetWritePoint();

			data->cmd = 92;

			printf("[Room %d Created] \n", m_roomStruct[i]->roomInfo.index);
			_user->SetRoomNum(m_roomStruct[i]->roomInfo.index);

			SortAscending();

			MakeRoomList();

			data->roomNum = m_roomStruct[i]->roomInfo.index;
			data->size = sizeof(UserData);

			//_data->Write(data->size);

			_user->Send(reinterpret_cast<char*>(data), sizeof(UserData));

			m_locker.LeaveLock();

			return true;
		}
	}

	printf("[�� ���� ����] \n");

	m_locker.LeaveLock();

	return false;
}

bool RoomManager::JoinRoom(NewRingBuffer* _data, User* _user, int tempNum)
{
	//������ ���� ����.
	if (tempNum == NULL)
	{
		printf("[������ ���� ����. (NULL ����)]\n");

		return false;
	}

	m_locker.EnterLock();

	int tempRoomIndex = 0;
	for (int i = 0; i < m_roomCount; i++)
	{
		if (m_roomStruct[i]->roomInfo.index == tempNum && 
			m_roomStruct[i]->roomInfo.count < m_roomStruct[i]->roomInfo.complement && 
			!m_roomStruct[i]->roomInfo.isPlaying)
		{
			UserData* data = (UserData*)_data->GetWritePoint();
			RoomStruct<User>* tempRoom = m_roomStruct[i];

			tempRoom->roomInfo.count = tempRoom->roomInfo.count + 1;
			tempRoom->user[1] = _user;

			printf("[Join %d Room]\n", tempRoom->roomInfo.index);
			_user->SetRoomNum(tempRoom->roomInfo.index);

			MakeRoomList();

			data->cmd = 94;
			data->roomNum = tempRoom->roomInfo.index;
			data->size = sizeof(UserData);

			//_data->Write(data->size);

			_user->Send(reinterpret_cast<char*>(data), sizeof(UserData));

			return true;
		}
	}

	printf("[�ش� �� ��ȣ�� ����]\n");

	//_data->Write(m_sendNoRoom->size);

	_user->Send(reinterpret_cast<char*>(m_sendNoRoom), sizeof(SendChatting));

	m_locker.LeaveLock();

	return false;
}

bool RoomManager::ExitRoom(NewRingBuffer* _data, User* _user)
{
	if (_user->GetSessionInfo().roomNum == NULL)
	{
		printf("[���� ���� ����]\n");

		return false;
	}

	m_locker.EnterLock();

	UserData* data = (UserData*)_data->GetWritePoint();

	data->cmd = 93;

	bool tmp = false;
	//�ش� �濡 ������ �� �ִ��� �˻�
	RoomStruct<User>* tempRoom = FindRoom(_user->GetSessionInfo().roomNum);

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (tempRoom->user[i]->GetSessionInfo().userID != _user->GetSessionInfo().userID)
		{
			tmp = true;

			break;
		}
	}

	//�ٸ� ����� ������ ���� ���ΰ� ���常
	if (tmp)
	{
		printf("[Left Room %d]\n", _user->GetSessionInfo().roomNum);

		this->LeaveRoom(_user);

		_user->SetRoomNum(0);
		_user->SetIsReady(false);

		MakeRoomList();

		data->roomNum = 0;
		data->size = sizeof(UserData);

		//_data->Write(data->size);

		_user->Send(reinterpret_cast<char*>(data), sizeof(UserData));

		m_locker.LeaveLock();

		return true;
	}

	//���� �������̿����� �� ���Ľ�Ű�� ����
	this->DestroyRoom(_user);

	printf("[Room %d Destroyed]\n", _user->GetSessionInfo().roomNum);
	_user->SetRoomNum(0);
	_user->SetIsReady(false);

	MakeRoomList();

	data->roomNum = 0;
	data->size = sizeof(UserData);

	//_data->Write(data->size);

	_user->Send(reinterpret_cast<char*>(data), sizeof(UserData));

	m_locker.LeaveLock();

	return true;
}

void RoomManager::LeaveRoom(User* _user)
{
	RoomStruct<User>* tempRoom = FindRoom(_user->GetSessionInfo().roomNum);

	tempRoom->roomInfo.count = tempRoom->roomInfo.count - 1;

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (tempRoom->user[i]->GetSessionInfo().socket == _user->GetSessionInfo().socket)
		{
			if (i == 0)
			{
				tempRoom->user[0] = m_roomStruct[i]->user[1];

				memset(&tempRoom->user[1], 0, sizeof(tempRoom->user[1]));
			}
			else if (i == 1)
			{
				memset(&tempRoom->user[1], 0, sizeof(tempRoom->user[1]));
			}
		}
	}
}

void RoomManager::DestroyRoom(User* _user)
{
	//printf("Start Destroying Room \n");

	for (int i = 0; i < ROOMMAX; i++)
	{
		if (_user->GetSessionInfo().roomNum == m_roomStruct[i]->roomInfo.index)
		{
			RoomsUpdate(i);

			return;
		}
	}
}

bool RoomManager::ReadyCheck(RoomStruct<User>* _tempRoom)
{
	bool isAllReady = true;

	if (_tempRoom->roomInfo.count < _tempRoom->roomInfo.complement) isAllReady = false;

	for (int i = 0; i < _tempRoom->roomInfo.count; i++)
	{
		if (!_tempRoom->user[i]->GetSessionInfo().isReady) isAllReady = false;
	}

	if (isAllReady)
	{
		InGameUserInfo* temp = (InGameUserInfo*)malloc(2);

		for (int i = 0; i < _tempRoom->roomInfo.count; i++)
		{
			if (i == 0)
			{
				UserData* data = (UserData*)_tempRoom->user[i]->GetSendBuffer()->GetReadPoint();

				data->cmd = 198;
				data->size = sizeof(UserData);

				_tempRoom->user[i]->Send(reinterpret_cast<char*>(data), sizeof(UserData));

				temp[0].user = _tempRoom->user[i]->GetSessionInfo();
				temp[0].order = 0;
			}
			else if (i == 1)
			{
				UserData* data = (UserData*)_tempRoom->user[i]->GetSendBuffer()->GetReadPoint();

				data->cmd = 199;
				data->size = sizeof(UserData);

				_tempRoom->user[i]->Send(reinterpret_cast<char*>(data), sizeof(UserData));

				temp[0].user = _tempRoom->user[i]->GetSessionInfo();
				temp[0].order = 1;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

void RoomManager::GomokuGridPacket(NewRingBuffer* _data, userInformation* _tempRoom, char* _packet)
{
	GomokuGrid* data = (GomokuGrid*)_data->GetWritePoint();

	RoomStruct<User>* tempRoom = FindRoom(_tempRoom->roomNum);

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (_tempRoom->userID != tempRoom->user[i]->GetSessionInfo().userID)
		{
			data->cmd = 200;

			//_data->Write(data->size);

			tempRoom->user[i]->Send(reinterpret_cast<char*>(data), sizeof(GomokuGrid));
		}
	}
}

void RoomManager::GomokuResultPacket(NewRingBuffer* _data, userInformation* _tempRoom, char* _packet)
{
	GomokuResult* data = (GomokuResult*)_data->GetWritePoint();

	RoomStruct<User>* tempRoom = FindRoom(_tempRoom->roomNum);

	for (int i = 0; i < tempRoom->roomInfo.count; i++)
	{
		if (_tempRoom->userID != tempRoom->user[i]->GetSessionInfo().userID)
		{
			data->cmd = 201;

			//_data->Write(data->size);

			tempRoom->user[i]->Send(reinterpret_cast<char*>(data), sizeof(GomokuResult));
		}
	}
}

void RoomManager::RoomsUpdate(int _num)
{
	if (_num < m_roomCount - 1)
	{
		m_roomNum.push_back(m_roomStruct[_num]->roomInfo.index);
	}
		
	if (m_roomCount >= 2)
	{
		m_roomStruct[_num]->Reset();
		ReturnObject(m_roomStruct[_num]);

		for (int i = _num; i < m_roomCount - 1; i++)
		{
			m_roomStruct[i] = m_roomStruct[i + 1];
		}

		m_roomStruct[m_roomCount - 1] = NULL;
		m_roomCount--;

		this->SortAscending();
	}
	else
	{
		m_roomStruct[m_roomCount - 1]->Reset();
		ReturnObject(m_roomStruct[m_roomCount - 1]);

		m_roomStruct[m_roomCount - 1] = NULL;
		m_roomCount--;
	}
}

void RoomManager::SortAscending()
{
	for (int i = 0; i < m_roomCount - 1; i++)
	{
		for (int j = i + 1; j < m_roomCount; j++)
		{
			if (m_roomStruct[i]->roomInfo.index > m_roomStruct[j]->roomInfo.index)
			{
				RoomStruct<User> *temp;
				temp = m_roomStruct[j];
				m_roomStruct[j] = m_roomStruct[i];
				m_roomStruct[i] = temp;
			}
		}
	}
}

void RoomManager::MakeRoomList()
{
	/*int tempNum = 0;

	for (int i = 0; i < 12; i++)
	{
		if (m_roomStruct[i] == NULL) break;

		m_roomListInfo_1->roomList[i] = m_roomStruct[i]->roomInfo;

		tempNum++;
	}

	m_roomListInfo_1->cmd = 96;
	m_roomListInfo_1->count = tempNum;
	m_roomListInfo_1->arraySize = m_roomListInfo_1->count * sizeof(SendingRoomStruct);
	m_roomListInfo_1->size = 20 + m_roomListInfo_1->arraySize;

	if (m_roomCount <= 12) return;

	tempNum = 0;

	for (int i = 12; i < 24; i++)
	{
		if (m_roomStruct[i] == NULL) break;

		m_roomListInfo_2->roomList[i] = m_roomStruct[i]->roomInfo;

		tempNum++;
	}

	m_roomListInfo_2->cmd = 96;
	m_roomListInfo_2->count = tempNum;
	m_roomListInfo_2->arraySize = m_roomListInfo_2->count * sizeof(SendingRoomStruct);
	m_roomListInfo_2->size = 20 + m_roomListInfo_2->arraySize;

	if (m_roomCount <= 24) return;

	tempNum = 0;

	for (int i = 24; i < 36; i++)
	{
		if (m_roomStruct[i] == NULL) break;

		m_roomListInfo_3->roomList[i] = m_roomStruct[i]->roomInfo;

		tempNum++;
	}

	m_roomListInfo_3->cmd = 96;
	m_roomListInfo_3->count = tempNum;
	m_roomListInfo_3->arraySize = m_roomListInfo_3->count * sizeof(SendingRoomStruct);
	m_roomListInfo_3->size = 20 + m_roomListInfo_3->arraySize;

	if (m_roomCount <= 48) return;

	tempNum = 0;

	for (int i = 36; i < 48; i++)
	{
		if (m_roomStruct[i] == NULL) break;

		m_roomListInfo_4->roomList[i] = m_roomStruct[i]->roomInfo;

		tempNum++;
	}

	m_roomListInfo_4->cmd = 96;
	m_roomListInfo_4->count = tempNum;
	m_roomListInfo_4->arraySize = m_roomListInfo_4->count * sizeof(SendingRoomStruct);
	m_roomListInfo_4->size = 20 + m_roomListInfo_4->arraySize;

	if (m_roomCount > 48)
	{
		tempNum = 0;

		for (int i = 48; i < 50; i++)
		{
			if (m_roomStruct[i] == NULL) break;

			m_roomListInfo_5->roomList[i] = m_roomStruct[i]->roomInfo;

			tempNum++;
		}

		m_roomListInfo_5->cmd = 96;
		m_roomListInfo_5->count = tempNum;
		m_roomListInfo_5->arraySize = m_roomListInfo_5->count * sizeof(SendingRoomStruct);
		m_roomListInfo_5->size = 20 + m_roomListInfo_5->arraySize;
	}*/
}