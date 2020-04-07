#pragma once
#include <vector>
#include <algorithm>
#include "packet.h"

#include "User.h"
#include "NewRingBuffer.h"

#include "ObjectPool.h"
#include "CriticalSectionClass.h"

#define ROOMMAX 50

using namespace std;

//=====================================================

//RoomManager

//�� ���� ������ RoomStruct ����ü�� ����

//�߰��� ������ ���� ��ȣ�� vector�� �����ص�.
//	������ �� ��ȣ �����ص� ���� = �߰����� ������ �� ��ȣ�� �����صּ� �� ������ �� �Ҵ��ϱ� ����

//������ ������ �ٷ� ���� ���ش�.

//SendRoomUserListToOther_�� �ΰ��� ����
//���� �Լ��� ���� �� ��ȣ�� �������� ���� �̹� ������ �������� ������ �� ��ȣ�� ������ �� ��� ��� - ������ ������ �� ��ȣ�� ���� �ҷ��ͼ� �������ְ��ִ�.
//�Ʒ��� �Լ��� ������ �濡�� ���� ��Ȳ�� �ƴ϶� ���� ���������� �� ��ȣ�� ������ �� �����Ƿ� ���

//20191010 - ���� or �߰� �����ؾ��� ����
//1. ���� �뿡�� ������ ���� �������� ���嵵 ���ϰ� Ŭ�󿡼� ǥ�⵵ ���ϰ� �־���.							(ǥ��Ϸ�)
// # ��� ���� ������ �������� �˷�����ұ�? ���� ���� ���� �� �׳� ExitRoom���� �ٷ� ���� �� #
//2. ���� ������ �� ���� ���� �ð��� ����. ��� �Ǳ��ϴµ� ���� ���ӿ��� �ʿ��� ����̹Ƿ�...				(�����ʾ���. ���� �ʿ�� ����.)

//CreateRoom, JoinRoom, ExitRoom�� ���ÿ� ������ ������ ���ɼ��� �����Ƿ� ���� CriticalSection���� ���Ƶξ���.

//=====================================================

class RoomManager : public ObjectPool<RoomStruct<User>>
{
private:
	//vector<RoomStruct<User>> vRoomList;

	RoomStruct<User>*		m_roomStruct[ROOMMAX];
	//�߰��� �� ���� ��ȣ �ִ� ����
	vector<int>				m_roomNum;

	int						m_roomCount;

	//==================================================

	SendChatting*			m_sendNoRoom;

	CriticalSectionClass	m_locker;

	//==================================================

	//�� ���������� 1����
	CreatedRoomList*		m_roomListInfo_1;
	CreatedRoomList*		m_roomListInfo_2;
	CreatedRoomList*		m_roomListInfo_3;
	CreatedRoomList*		m_roomListInfo_4;
	CreatedRoomList*		m_roomListInfo_5;

public:
	RoomManager();
	~RoomManager();
	
	void Init();

	RoomStruct<User>* FindRoom(int _roomNum);

	//�� ���� ä�� ����
	void SendChattAll_Room(int _roomNum, SendChatting* _packet);

	//�� �����ο� ���� �Ѹ���
	void SendRoomUserList(NewRingBuffer* _data, User* _user);
	//�� �� �ٸ� �����ο��鿡�� �����ο� ���� �Ѹ���
	void SendRoomUserListToOther(NewRingBuffer* _data, int _roomNum);
	void SendRoomUserListToOther(NewRingBuffer* _data, User* _user);

	void RoomUserUpdate(User* _user);

	bool CreateRoom(NewRingBuffer* _data, User* _user);

	bool JoinRoom(NewRingBuffer* _data, User* _user, int tempNum);

	bool ExitRoom(NewRingBuffer* _data, User* _user);
	void LeaveRoom(User* _user);
	void DestroyRoom(User* _user);

	bool ReadyCheck(RoomStruct<User>* _tempRoom);
	void GomokuGridPacket(NewRingBuffer* _data, userInformation* _tempInfo, char* _packet);
	void GomokuResultPacket(NewRingBuffer* _data, userInformation* _tempInfo, char* _packet);

	void RoomsUpdate(int _num);
	void SortAscending();

	void MakeRoomList();

	int GetRoomCount() { return m_roomCount; }
	RoomStruct<User>* GetRoom(int num) { return m_roomStruct[num]; }

	CreatedRoomList* GetCreatedRoomList_1() { return m_roomListInfo_1; }
	CreatedRoomList* GetCreatedRoomList_2() { return m_roomListInfo_2; }
	CreatedRoomList* GetCreatedRoomList_3() { return m_roomListInfo_3; }
	CreatedRoomList* GetCreatedRoomList_4() { return m_roomListInfo_4; }
	CreatedRoomList* GetCreatedRoomList_5() { return m_roomListInfo_5; }
};