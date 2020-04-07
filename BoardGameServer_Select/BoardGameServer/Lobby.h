#pragma once
#include <vector>

#include "packet.h"
#include "RoomManager.h"

class Channel;

//=====================================================

//Lobby

//�Ѱ��� SelectClass �ϳ��� Lobby �ϳ� �� �� (Channel ���� ��)
//�κ� ������ �迭�� ������
//SelectClass�ʹ� ��ȣ���� ����

//�� ���� ����Ʈ�� ������ 2���̹Ƿ� �ٷιٷ� ��� �������� �� ���� ����Ʈ�� �����ش�.

//SendLobbyUserListToOther �Լ��� �ǹ̰� �ֳ�? ������ ����� ���ΰ�ħ�� ���� ��쿡�� ���Ž����ֹǷ� ������.
//					 (�ڵ����� �����ְԵǸ� ����ҵ�)

// =========== �׽�Ʈ ���� ������ =============
//�κ� ���� ����Ʈ and �� ����Ʈ�� Ŭ�󿡼� ���ΰ�ħ �䱸�ÿ��� ���� ����Ʈ�� �����ش�.
//                   (�ڵ����� �����ִ°� �Ƹ� �κ� ���� ����Ʈ���� ������ ���� ����)

//ps
//���� �Լ����ε� �ڿ� _������ ���Ź���

//=====================================================

class Lobby
{
private:
	RoomManager				roomManager;

	userInformation*		lobbyUserArray[100];
	int						userNum;

	vector<RoomStruct>		vRoomList;

	Channel*			channel;

public:
	Lobby();
	~Lobby();

	void Init();
	void LobbyUserUpdata(userInformation* _userInfo, bool _goRoom);
	//�κ� �����ο� ��ü�� ä�� ������
	void SendChatAll_Lobby(SendChatting* _packet);

	//�κ� ���� ����Ʈ ������
	void SendLobbyUserList(userInformation* _info);
	//�� ����Ʈ ������
	void SendRoomList(userInformation* _info, ReqRoomListData* _packet);

	//=============================================================================

	//�κ� �����ο� ���� ������
	void SendLobbyUserList_(userInformation* _info);
	void SendLobbyUserListToOther_(userInformation* _info);

	//=============================================================================

	void pushBackLobbyUser(userInformation* _session);
	void LogOut(userInformation* info);
	void UserUpdate(int _num);

	void SetChannelData(Channel* _channel) { channel = _channel; }

	userInformation getLobbyUser(int num) { return *lobbyUserArray[num - 1]; }

	Channel* getChannelClass() { return channel; }
	RoomManager* getRoomManager() { return &roomManager; }

	void ShowLobbyUserList()
	{
		printf("----------------------- \n");
		printf("Lobby User list \n");

		for (int i = 0; i < userNum; i++)
		{
			printf("%s \n", lobbyUserArray[i]->name);
		}

		printf("----------------------- \n");
	}
};