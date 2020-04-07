#pragma once
#include <vector>
#include <algorithm>
#include "packet.h"

//#include "Room.h"

#define ROOMMAX 50

using namespace std;

//=====================================================

//RoomManager

//�� ���� ������ RoomStruct ����ü�� ����

//�߰��� ������ ���� ��ȣ�� vector�� �����ص�.
//	������ �� ��ȣ �����ص� ���� = �߰����� ������ �� ��ȣ�� �����صּ� �� ������ �� �Ҵ��ϱ� ����

//SelectClass�� ��ȣ����

//������ ������ �ٷ� ���� ���ش�.

//SendRoomUserListToOther_�� �ΰ��� ����
//���� �Լ��� ���� �� ��ȣ�� �������� ���� �̹� ������ �������� ������ �� ��ȣ�� ������ �� ��� ���
//�Ʒ��� �Լ��� ������ �濡�� ���� ��Ȳ�� �ƴ϶� ���� ���������� �� ��ȣ�� ������ �� �����Ƿ� ���
// # �ֱٿ� �� �����ε� ���� �̷��� �� �ʿ䰡 �ֳ�? # - ���� ����

//20191010 - ���� or �߰� �����ؾ��� ����
//1. ���� �뿡�� ������ ���� �������� ���嵵 ���ϰ� Ŭ�󿡼� ǥ�⵵ ���ϰ� �־���.
// # ��� ���� ������ �������� �˷�����ұ�? ���� ���� ���� �� �׳� ExitRoom���� �ٷ� ���� �� #
//2. ���� ������ �� ���� ���� �ð��� ����. ��� �Ǳ��ϴµ� ���� ���ӿ��� �ʿ��� ����̹Ƿ�...

//ps
//���� �Լ����ε� �ڿ� _������ ���Ź���

//=====================================================

class Channel;

class RoomManager
{
private:
	RoomStruct* roomStruct[ROOMMAX];
	//�߰��� �� ���� ��ȣ �ִ� ����
	vector<int> roomNum;

	int roomCount = 0;

	Channel* channel;

	//==================================================

	SendChatting* sendNoRoom;

public:
	RoomManager();
	~RoomManager();
	
	void Init();

	//�� ���� ä�� ����
	void SendChattAll_Room(int _roomNum, SendChatting* _packet);

	void SendRoomUserList(userInformation* _info, ParticipantsInfo* _packet);

	// ========================================================

	//�� �����ο� ���� �Ѹ���
	void SendRoomUserList_(userInformation* _info);
	//�� �� �ٸ� �����ο��鿡�� �����ο� ���� �Ѹ���
	void SendRoomUserListToOther_(int _roomNum);
	void SendRoomUserListToOther_(userInformation* _info);

	// ========================================================

	void RoomUserUpdate(userInformation* _info);

	bool CreateRoom(userInformation* _info);

	bool JoinRoom(userInformation* _info, int tempNum);

	bool ExitRoom(userInformation* _info);
	void LeaveRoom(userInformation* _info);
	void DestroyRoom(userInformation* _info);

	void ReadyCheck(RoomStruct* _tempRoom);
	void GomokuGridPacket(userInformation* _tempInfo, char* _packet);
	void GomokuResultPacket(userInformation* _tempInfo, char* _packet);

	void RoomsUpdate(int _num);
	void SortAscending();

	void SetChannelData(Channel* _channel) { channel = _channel; }

	int getRoomCount() { return roomCount; }

	//RoomStruct* getRooms() { return roomStruct; }
	RoomStruct* getRoom(int num) { return roomStruct[num]; }
	int getRoomIndex(int num) { return roomStruct[num]->roomInfo.index; }

	/*Room getRoom(int num) { return *room[num]; }
	int getRoomIndex(int i) { return room[i]->getIndex(); }*/
};