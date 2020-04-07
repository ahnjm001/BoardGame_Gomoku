#include "ChannelManager.h"

ChannelManager::ChannelManager()
{
	//portNum = 30002;

	//portNum++;

	if (!channelArray[0].Init(30002))
	{
		printf("Channel Init Error \n");
	}

	handleArray[0] = channelArray[0].GetHandle();

	if(!channelArray[1].Init(30003))
	{
		printf("Channel Init Error \n");
	}

	handleArray[1] = channelArray[1].GetHandle();

	if (!channelArray[2].Init(30004))
	{
		printf("Channel Init Error \n");
	}

	handleArray[2] = channelArray[2].GetHandle();

	channelNum = CHANNELNUM;
}

ChannelManager::~ChannelManager()
{
}

void ChannelManager::CloseChannels()
{
	closesocket(channelArray[0].GetListenSocket());
	closesocket(channelArray[1].GetListenSocket());
	closesocket(channelArray[2].GetListenSocket());

	//WSACleanup();
}

//�׽��ÿ�
void ChannelManager::ShowChannelList()
{
	for (int i = 0; i < channelNum; i++)
	{
		printf("%d, ", i);
	}

	printf("\n");
}


//������ �κ�
void ChannelManager::LoopRun()
{
	channelArray[0].Start(&channelArray[0]);
	channelArray[1].Start(&channelArray[1]);
	channelArray[2].Start(&channelArray[2]);

	WaitForMultipleObjects(CHANNELNUM, handleArray, true, INFINITE);

	while (1)
	{
		
	}

	/*
	while (1)
	{
		for (int i = 0; i < channelNum; i++)
		{
			//Ư�� ä���� ��á��.
			if (channelArray[i]->GetIsFull())
			{
				//ä�� �ϳ� �� �߰�
				channelArray[channelNum] = PopObject();
				channelArray[channelNum]->Init(portNum);
				channelArray[channelNum]->Start(channelArray[channelNum]);

				portNum++;

				//���� Ż��
				break;
			}
		}

		for (int i = 0; i < channelNum; i++)
		{
			//Ư�� ä���� ����� && ������ ä���� �ƴϴ�.
			if (channelArray[i]->GetIsEmpty() && i != 0)
			{
				//ä���� ������Ʈ Ǯ�� �ٽ� �ݳ�
				ReturnObject(channelArray[i]);

				//���� �߰� ä���� ������� �ȴٸ� �߰��� �� ä���� ä�����Ѵ�.
				while (i == channelNum - 1)
				{
					//������ ä�� �� �κ��� ä�ε���
					//�ϳ��� �� ������ ä��� ���� ������ ����.
					channelArray[i] = channelArray[i + 1];
					i++;
				}

				//������ �κ��� ����
				channelArray[i] = NULL;
				//�������ִ� ä���� ������ �Ѱ� �پ���.
				channelNum--;
				
				//���� Ż��
				break;
			}
		}

		ShowChannelList();
	}
	*/
}