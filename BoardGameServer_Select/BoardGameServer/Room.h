//#pragma once
//#include "packet.h"
//#include <vector>
//
//using namespace std;
//
//class Room
//{
//	int index = 0;		//�� ��ȣ
//	int count = 0;		//�ο���
//	int complement = 6;	//����
//
//	vector<userInformation>				userInfo_inRoom;
//	vector<userInformation>::iterator	userInfo_inRoom_iter;
//
//public:
//	Room();
//	~Room();
//
//	int getComplement() { return complement; }
//
//	int getIndex() { return index; }
//	void setIndex(int _num) { index = _num; }
//
//	int getCount() { return count; }
//	void setCount(int _num) { count = _num; }
//
//	vector<userInformation> getUserInfo_inRoom() { return userInfo_inRoom; }
//
//	void setUserInfo_inRoom(userInformation _info) { userInfo_inRoom.push_back(_info); }
//	void deleteUserInfo_inRoom(userInformation _info)
//	{
//		for (int i = 0; i < userInfo_inRoom.size(); i++)
//		{
//			if (userInfo_inRoom[i].socket == _info.socket)
//			{
//				userInfo_inRoom.erase(userInfo_inRoom.begin() + i);
//			}
//		}
//	}
//};
//
