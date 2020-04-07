#pragma once
#include "stdafx.h"
#include "CriticalSectionClass.h"

//����̰� ������ ���ߴ� ������� ������ ���� ¥��
//�Ľ� �κ��� �� �� ���� ���� �ͺ��� źź��

//Init���� �� ���� ���̿� �ӽ� ���� ����� ����
//���۸� �޴ٰ� ������ �Ѿ�ԵǸ� ������ ��� ���
//��Ŷ�� �߷��� ��쿡 �� �κ� ��Ŷ�� memcpy����(1����Ʈ�� �����ǹ��� �󸶳� �߸��簣�� �߷����� �׳� memcpy�ϹǷ� ���� �߻� x)

//20191118
//�����۰� ����� ¥������ ���� ſ�� Ŭ��,������ ���� �Ҿ����ߴ�. ��ġ�ϱ� �ߵ�

class NewRingBuffer
{
private:
	//���� �ּ�
	char*		buffer;
	//������ ���� ����
	char*		bufferStartPoint;
	//���� ������
	int			bufferMaxSize;
	//�ӽ� ���� ���� ������
	int			tempBufferSize;

	//�д� ����
	char*		readPoint;
	//���� ����
	char*		writePoint;

	CriticalSectionClass locker;

public:
	NewRingBuffer();
	~NewRingBuffer();

	//Initializing
	void Init(int _size, int _tempSize);
	//�ʱ�ȭ
	void Reset();
	//_size��ŭ �б�
	void Write(int _size);
	void Read(int _size);
	//�Ľ� �������� ���� üũ
	bool CanParsing();
	//�Ľ�
	char* Parsing();

	//�� �� �ִ� ������ ũ�� ���
	DWORD GetWriteableSize();
	DWORD GetReadableSize();
	//������ �ȿ� �ִ� �������� �� ũ��
	DWORD GetDataInBuffer();
	//��Ŷ ������ 
	unsigned short GetPacketSize();

	char* GetWritePoint() { return writePoint; }
	char* GetReadPoint() { return readPoint; }
	int GetBufferSize() { return bufferMaxSize; }
};



//DB ���� �ֱ�
//���� : ���� �����
//
//	Session �����->DB���� & �������� ����
//
//	MySQL - ���ڼ� ���� ?
//
//
//	SERVER-- > RAM Cache-- > MySQL
//	DB Agent
//	MsSQL
//	Oracle