#include "NewRingBuffer.h"

NewRingBuffer::NewRingBuffer()
{
	
}

NewRingBuffer::~NewRingBuffer()
{

}

void NewRingBuffer::Init(int _size, int _tempSize)
{
	bufferMaxSize = _size;
	tempBufferSize = _tempSize;

	buffer = new char[_size];

	bufferStartPoint = buffer + tempBufferSize;
	writePoint = readPoint = bufferStartPoint;
}

void NewRingBuffer::Reset()
{
	//���۸� ������
	//SAFE_DELETE_ARRAY(buffer);

	//���ۿ� WP, RP �ʱ�ȭ
	buffer = bufferStartPoint - tempBufferSize;
	writePoint = readPoint = bufferStartPoint;
}

void NewRingBuffer::Write(int _size)
{
	writePoint += _size;

	if (writePoint >= buffer + bufferMaxSize)
	{
		writePoint = bufferStartPoint;
	}
}

void NewRingBuffer::Read(int _size)
{
	readPoint += _size;

	if (readPoint >= buffer + bufferMaxSize)
	{
		readPoint = bufferStartPoint;
	}
}

bool NewRingBuffer::CanParsing()
{
	DWORD dataInBuffer = GetDataInBuffer();

	//������ �ȿ� �����Ͱ� 2�̻� �ִ°�? (��Ŷ ������ ���� �� �ִ� �ּ����� ũ�� = 2)
	if (dataInBuffer >= 2)
	{
		return true;
	}

	//�����Ͱ� ���ų� 1���ͼ� ũ������ �� �� ���� ���
	return false;
}

char* NewRingBuffer::Parsing()
{
	//������ ���������� �д� ���������� ������
	DWORD remainedSize = (buffer + bufferMaxSize) - readPoint;
	//�Ľ��� �����ʹ� �д� �������� �о�´�.
	char* parsingData = readPoint;

	//������ ���������� �д� �������� ����� 1�ۿ� ���� ��� -> �̾�����Ѵ�.
	if (remainedSize == 1)
	{
		char* tempBuffer = bufferStartPoint - 1;

		*tempBuffer = *readPoint;

		locker.EnterLock();
		parsingData = readPoint = tempBuffer;
		locker.LeaveLock();

		readPoint += GetPacketSize();

		return parsingData;
	}
	//������ ���������� �д� ������ ���� = ������ ù�������� �д� ������ �Űܾ��Ѵ�.
	else if (remainedSize == 0)
	{
		locker.EnterLock();
		readPoint = bufferStartPoint;
		locker.LeaveLock();
	}

	unsigned short packetSize = GetPacketSize();

	if (packetSize > remainedSize)
	{
		memcpy(bufferStartPoint - remainedSize, readPoint, remainedSize);
		parsingData = readPoint = (bufferStartPoint - remainedSize);
	}

	readPoint += packetSize;
	return parsingData;
}

//readPoint�� writePoint�� ���� �� ó��
//����ȭ ����
//		-> Parsing�ʿ��� ReadPoint�� �Ű����� Lock�� �ɾ����(191202)

DWORD NewRingBuffer::GetWriteableSize()
{
	if (readPoint < writePoint)
	{
		return (buffer + bufferMaxSize) - writePoint;
	}
	else if (readPoint == writePoint)
	{
		//readPoint�� writePoint�� ������
		//�����Ͱ� �ִ� ��� == �ѹ��� ���Ƽ� ������
		if (this->GetDataInBuffer() > 0)
		{
			return 0;
		}
		//readPoint�� writePoint�� ������
		//�����Ͱ� ���� ��� == ringBuffer�� �����͸� �޴� �����̰ų� ó���Ұ� ����(����X)
		else
		{
			return (buffer + bufferMaxSize) - writePoint;
		}
	}
	else
	{
		return readPoint - writePoint;
	}
}

DWORD NewRingBuffer::GetReadableSize()
{
	if (readPoint <= writePoint)
	{
		return writePoint - readPoint;
	}
	else
	{
		return (buffer + bufferMaxSize) - readPoint;
	}
}

DWORD NewRingBuffer::GetDataInBuffer()
{
	if (readPoint > writePoint)
	{
		return (buffer + bufferMaxSize) - readPoint + (writePoint - bufferStartPoint);
	}
	else
	{
		return (int)(writePoint - readPoint);
	}
}

unsigned short NewRingBuffer::GetPacketSize()
{
	return *(unsigned short*)readPoint;
}