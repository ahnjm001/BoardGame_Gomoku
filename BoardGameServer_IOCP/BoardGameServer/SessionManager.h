#pragma once
#include <algorithm>

#include "ObjectPool.h"
#include "CriticalSectionClass.h"

//=====================================================

//SessionManager

//Session���� �����ϱ����� �Ŵ���

//ObjectPool�� ��ӹ޾� ���� ������ �̸� User�� 100���� �����д�.

//CreateSession�� Accept�� ���� �����̹Ƿ� ���ÿ� ������ �������� �����Ƿ� CriticalSection�� ������� �ʾ�����
//DeleteSession������ ���ÿ� ������ Session�� �����ϰ� ������ �� �����Ƿ� CriticalSection���� ���Ƶξ���.	

//=====================================================

template <typename T>
class SessionManager : public ObjectPool<T>
{
private:
	int						m_count;

	vector<T*>				m_vSessionList;

	CriticalSectionClass	m_locker;

public:
	SessionManager()
	{	
	}

	~SessionManager()
	{
	}

	void Init()
	{
		m_count = 0;
	}

	T* CreateSession()
	{
		m_count++;

		return ObjectPool<T>::PopObject();
	}

	void DeleteSession(T* _t)
	{
		m_locker.EnterLock();

		typename vector<T*>::iterator iter = 
			find(m_vSessionList.begin(), m_vSessionList.end(), _t);
		m_vSessionList.erase(iter);

		ObjectPool<T>::ReturnObject(_t);

		m_locker.LeaveLock();
	}

	void AddSessionList(T* _t)
	{
		m_vSessionList.push_back(_t);
	}

	vector<T*> GetSessionList() { return m_vSessionList; }
	int GetCount() { return m_count; }
};