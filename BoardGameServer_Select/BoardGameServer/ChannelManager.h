#pragma once
//#include "ObjectPool.h"
#include "ThreadClass.h"

#include "Channel.h"

#define CHANNELNUM 3

//������Ʈ Ǯ ����
//https://developstudy.tistory.com/44

//=====================================================

//ChannelManager

//������ ���� ��
//ä�θ��� ��Ʈ��ȣ �ٸ��� �ؼ� ����ؾ��Ѵٰ� �Ѵ�. - HOW? ������ ���� �� ������
//		(���� ��Ʈ��ȣ�� Server�� Init�Լ����� �Ҵ�����. �̰ͺ��� �����ؾ���.)
//�̰� ���� �����ؾ� CS�� ���� ���θ� �� �� �ִ�.

//ObjectPool�� ä�� ���� �� ä�� �ʿ��� ������ ���� ����

//ThreadClass�� ��ӹ޾� Thread�� �����鼭 Channel ���� Ȥ�� ��Ⱑ �ʿ����� ��� üũ

//=====================================================

class ChannelManager : /*public ObjectPool<Channel> , */public ThreadClass<ChannelManager>
{
private:
	Channel channelArray[CHANNELNUM];
	HANDLE	handleArray[CHANNELNUM];

	int channelNum;
	int portNum;

public:
	ChannelManager();
	~ChannelManager();

	void CloseChannels();

	void ShowChannelList();

	void LoopRun();
};

