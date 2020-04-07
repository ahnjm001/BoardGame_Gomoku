#pragma once
#include <stack>

#include "CriticalSectionClass.h"

using namespace std;

//=====================================================

//ObjectPool

//=====================================================

template<typename T>
class ObjectPool
{
private:
	CriticalSectionClass locker;
	stack<T*> objects;

	// �ִ� �迭 ũ��
	int maxSize; 

public:
	int GetCount()
	{
		return objects.size();
	}

	// �����ŭ ������Ʈ�� �����.
	ObjectPool(int size = 100) 
	{
		maxSize = size;

		for (int i = 0; i < maxSize; ++i) 
		{
			T* newObject = new T();
			objects.push(newObject);
		}
	}

	// ������Ʈ�� ����.
	~ObjectPool()
	{
		locker.EnterLock();

		while (!objects.empty()) 
		{
			T* object = objects.top();
			objects.pop();
			delete object;
		}

		maxSize = 0;

		locker.LeaveLock();
	}

	// ������Ʈ�� ������.
	T* PopObject()
	{
		locker.EnterLock();

		// ������Ʈ�� ���ٸ� Ȯ���Ѵ�.
		if (objects.empty()) 
		{
			Expand();
		}

		T* retVal = objects.top();
		objects.pop();

		locker.LeaveLock();

		return retVal;
	}

	// ���� ũ�⸸ŭ ���ο� ������Ʈ�� �־� Ȯ���Ѵ�.
	void Expand() 
	{
		locker.EnterLock();

		// �ø� ũ�⸸ŭ ���ο� ������Ʈ�� �־��ش�.
		for (int i = 0; i < maxSize; ++i)
		{
			T* newObject = new T();
			objects.push(newObject);
		}

		// �ִ� ũ�⸦ �ø���.
		maxSize += maxSize;

		locker.LeaveLock();
	}

	// ������Ʈ�� �����Ѵ�.
	void ReturnObject(T* _object)
	{
		//locker.EnterLock();

		objects.push(_object);

		//locker.LeaveLock();
	}
};