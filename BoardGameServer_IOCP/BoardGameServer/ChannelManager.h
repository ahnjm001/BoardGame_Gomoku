#pragma once
#include "ThreadClass.h"

#include "Channel.h"

#define CHANNELNUM 3

//������Ʈ Ǯ ����
//https://developstudy.tistory.com/44

//=====================================================

//ChannelManager

//������ ���� ��
//ä�θ��� ��Ʈ��ȣ �ٸ��� �ؼ� ����ؾ��Ѵٰ� �Ѵ�. - HOW? ������ ���� �� ������
//		(���� ��Ʈ��ȣ�� Server�� Init�Լ����� �Ҵ�����.)
//�̰� ���� �����ؾ� CS�� ���� ���θ� �� �� �ִ�.

//ObjectPool�� ä�� ���� �� ä�� �ʿ��� ������ ���� ���� (���� ä�� ����Ʈ�� 3���� �������ѵּ� �̻����)

//ThreadClass�� ��ӹ޾� Thread�� �����鼭 Channel ���� Ȥ�� ��Ⱑ �ʿ����� ��� üũ (�̰Ͷ��� ���� ���̶� �� �����)

//=====================================================

class ChannelManager /*: public ObjectPool<Channel> , public ThreadClass<ChannelManager>*/
{
private:
	Channel m_channelArray[CHANNELNUM];

public:
	ChannelManager();
	~ChannelManager();

	void Init();
};

