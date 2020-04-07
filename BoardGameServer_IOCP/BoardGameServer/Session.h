#pragma once

#pragma warning(disable:4996)

#include "stdafx.h"

#include "NewRingBuffer.h"

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

//## Send�Լ�
//Lobby�� RoomManager���� SelectClass�� �ٽ� ������ Session�� ã�� Send�Լ��� �̿��� Send��

//=====================================================

//MMORPG ��������
//https://www.youtube.com/watch?v=yk-HD8YoyZg

//���Ӽ��������� ���̵�
//https://www.slideshare.net/devcatpublications/ndc2013-19986939

//����ü Ȯ��
//overlapped

struct ST_OVERLAPPED : public WSAOVERLAPPED
{
	class Session* session;
};

class Session
{
protected:
	userInformation	m_info;

	ST_OVERLAPPED m_recvOverlapped;
	WSABUF m_recvDataBuffer;

	ST_OVERLAPPED m_sendOverlapped;
	WSABUF m_sendDataBuffer;

	DWORD m_recvBytes;
	DWORD m_flags;

	DWORD m_sendBytes;

	NewRingBuffer*	m_recvBuffer;
	NewRingBuffer*  m_sendBuffer;

	bool m_isConnected;

private:

public:
	Session()
	{
		m_recvOverlapped.session = this;
		m_sendOverlapped.session = this;

		m_recvBuffer = new NewRingBuffer();
		m_recvBuffer->Init(5000, 100);

		m_sendBuffer = new NewRingBuffer();
		m_sendBuffer->Init(5000, 1000);

		m_recvBytes = 0;
		m_flags = 0;
		m_sendBytes = 0;

		m_isConnected = false;
	}

	~Session()
	{

	}

	//WSASend
	//������ �����ض�? - �̷��� �׽�Ʈ�ҋ� ����� ����ϴ�.
	//HOW?????????????????????

	//RECV SEND üũ��
	void CheckCompletion(ST_OVERLAPPED* _overlapped, DWORD _bytes)
	{
		if (_overlapped == &m_recvOverlapped)
		{
			//printf("[ m_recvBytes = %d ]\n", _bytes);

			if (_bytes <= 0)
			{
				//printf("[ SOCKET %d ���� ���� ] \n", m_info.socket);
				m_isConnected = false;
			}

			m_recvBuffer->Write(_bytes);

			Recv();
		}
		else
		{
			//Send(_bytes);
		}
	}

	void Recv()
	{
		m_recvDataBuffer.buf = m_recvBuffer->GetWritePoint();
		m_recvDataBuffer.len = m_recvBuffer->GetWriteableSize();

		if (WSARecv(
			m_info.socket,
			&m_recvDataBuffer,
			1,
			&m_recvBytes,
			&m_flags,
			&m_recvOverlapped,
			NULL)
			== SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			//printf("RECV IO PENDING FAILURE \n");
		}
	}

	void Send()
	{
		m_sendDataBuffer.buf = m_sendBuffer->GetWritePoint();
		m_sendDataBuffer.len = m_sendBuffer->GetWriteableSize();

		if (WSARecv(
			m_info.socket,
			&m_sendDataBuffer,
			1,
			&m_sendBytes,
			&m_flags,
			&m_sendOverlapped,
			NULL)
			== SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			//printf("RECV IO PENDING FAILURE \n");
		}
	}

	//�������� ���� �� �־��ָ� ������ ũ�� �Ȼ����.
	//But. Overlapped�� �ְ� �ٷ� delete�������. (������ �����ε��ؼ� ��)
	void Send(char* _data, DWORD _bytes)
	{
		m_sendDataBuffer.buf = _data;
		m_sendDataBuffer.len = _bytes;

		if (WSASend(
			m_info.socket,
			&m_sendDataBuffer,
			1,
			&m_sendBytes,
			0,
			&m_sendOverlapped,
			NULL)
			== SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("SEND IO PENDING FAILURE\n");
		}
	}

	userInformation GetSessionInfo() { return m_info; }

	NewRingBuffer* GetRecvBuffer() { return m_recvBuffer; }
	NewRingBuffer* GetSendBuffer() { return m_sendBuffer; }
											
	bool GetIsConnected() { return m_isConnected; }

	void SetIsReady(bool _bool) { m_info.isReady = _bool; }
	void SetRoomNum(int _num) { m_info.roomNum = _num; }
};