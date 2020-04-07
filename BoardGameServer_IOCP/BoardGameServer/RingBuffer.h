#pragma once
//https://jinheeahn.wordpress.com/2015/01/29/ringbuffer%EB%9E%80-%EC%99%9C-%EC%82%AC%EC%9A%A9%ED%95%98%EB%8A%94%EA%B0%80/

//https://phiru.tistory.com/104
#include "packet.h"

#pragma warning(disable:4996)

using namespace std;

//NewRingBuffer�� ����« ����

class RingBuffer
{
private:
	//���� ������
	int			bufferSize;
	//�ӽ� ���� ���� ������
	int			tempBufferSize;
	//���� �ּ�
	char*		buffer;
	//�д� ����
	char*		readPoint;
	//���� ����
	char*		writePoint;
	//������ ���� ����
	char*		bufferStartPoint;
	//������ �� ����
	char*		bufferEndPoint;
	//���� �� ������ ũ��
	int			dataInBuffer;

public:
	//������
	RingBuffer()
	{
		buffer = nullptr;
		readPoint = nullptr;
		writePoint = nullptr;
		bufferStartPoint = nullptr;
		bufferEndPoint = nullptr;
		bufferSize = 0;
		tempBufferSize = 0;
		dataInBuffer = 0;
	}
	~RingBuffer()
	{

	}

	//_size��ŭ ������ ����
	void Init(int _size)
	{
		buffer = new char[_size];
		if (buffer == nullptr) return;

		bufferSize = _size;

		this->Reset();
	}

	//����
	void Reset()
	{
		bufferStartPoint = buffer;
		bufferEndPoint = buffer + bufferSize;
		readPoint = buffer;
		writePoint = buffer;

		dataInBuffer = 0;
	}

	//wrirtePoint _size��ŭ �̵�
	void Write(int _size)
	{
		writePoint += _size;
		dataInBuffer += _size;

		if (writePoint == bufferEndPoint)
		{
			writePoint = buffer;
		}
	}

	//���� _size ��ŭ readPoint �̵�
	void Read(int _size)
	{
		readPoint += _size;

		if (readPoint >= bufferEndPoint)
		{
			readPoint = buffer + (readPoint - bufferEndPoint);
		}

		dataInBuffer -= _size;
	}

	//������ ������ ������ ũ��
	int GetDataInBuffer()
	{
		return dataInBuffer;
	}

	//write ������ ũ��
	int GetWriteSize()
	{
		if (readPoint <= writePoint)
		{
			return (int)(bufferEndPoint - writePoint);
		}
		else
		{
			return (int)(readPoint - writePoint);
		}
	}

	//Read ������ ũ��
	int GetReadSize()
	{
		if (readPoint <= writePoint)
		{
			return (int)(writePoint - readPoint);
		}
		else
		{
			return (int)(bufferEndPoint - readPoint);
		}
	}

	//writePoint ��ȯ
	char* GetWritePoint()
	{
		return writePoint;
	}

	//readPoint ��ȯ
	char* GetReadPoint()
	{
		return readPoint;
	}

	//		bufferEndPoint - _buffer ��
	int GetRemainedSize(char* _buffer) 
	{ 
		return (int)(bufferEndPoint - _buffer); 
	}

	int GetBufferSize()
	{
		return bufferSize;
	}
};