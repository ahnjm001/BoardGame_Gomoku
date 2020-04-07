#pragma once

#pragma warning(disable:4996)

#include "packet.h"
#include "RingBuffer.h"

/*
// Lee.ks - 190515
�� Ŭ���� ��Ȱ?????????

roomManager ( why ????? ) 
userinfo -- sessionmanager �� ������ �ִ� session buffer 

 ��� ����, �������� ������ �ȵ�
*/

//������ �α��� ���� ������ ���� ����Ѵ�.
//
//���� ���� �׽�Ʈ ����
//http://www.devkorea.co.kr/bbs/board.php?bo_table=m03_qna&wr_id=98817

//=====================================================

//Session

//Server�������� ������ Lobby ������ Ȱ�� �� Lobby�� RoomManager ����

//## Send�Լ�
//Lobby�� RoomManager���� SelectClass�� �ٽ� ������ Session�� ã�� Send�Լ��� �̿��� Send��

//=====================================================

template<typename T>
class Session
{
protected:
	//�ش� ������ ���� ����
	userInformation info;

	int				recvByte;
	char			sendData[5000];
	char*			savedBuffer;
	int				savedPosition;

	RingBuffer*		ringBuffer;

private:

public:
	Session()
	{
		ringBuffer = new RingBuffer();
		ringBuffer->Init(1000);

		savedBuffer = nullptr;
		savedPosition = 0;
	}

	~Session()
	{

	}

	virtual void Init(T* _t) = 0;
	virtual void Reset() = 0;
	virtual bool Recv() = 0;
	virtual bool Parsing() = 0;
	virtual void Send(void* _data, int _size) = 0;

	userInformation getSessionInfo() { return info; }
	RingBuffer* getRingBuffer() { return ringBuffer; }
};
