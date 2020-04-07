#pragma once
#include <stack>
#include <mutex>

using namespace std;

//=====================================================

//ObjectPool

//=====================================================

typedef lock_guard<recursive_mutex> MutexLocker;

template<typename T>
class ObjectPool
{
private:
	recursive_mutex mt;
	stack<T*> objects;

	// �ִ� �迭 ũ��
	int maxSize; 

public:
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
		MutexLocker locker(mt);

		while (!objects.empty()) 
		{
			T* object = objects.top();
			objects.pop();
			delete object;
		}

		maxSize = 0;
	}

	// ������Ʈ�� ������.
	T* PopObject()
	{
		MutexLocker locker(mt);

		// ������Ʈ�� ���ٸ� Ȯ���Ѵ�.
		if (objects.empty()) 
		{
			Expand();
		}

		T* retVal = objects.top();
		objects.pop();
		return retVal;
	}

	// ���� ũ�⸸ŭ ���ο� ������Ʈ�� �־� Ȯ���Ѵ�.
	void Expand() 
	{
		MutexLocker locker(mt);

		// �ø� ũ�⸸ŭ ���ο� ������Ʈ�� �־��ش�.
		for (int i = 0; i < maxSize; ++i)
		{
			T* newObject = new T();
			objects.push(newObject);
		}

		// �ִ� ũ�⸦ �ø���.
		maxSize += maxSize;
	}

	// ������Ʈ�� �����Ѵ�.
	void ReturnObject(T* _object)
	{
		MutexLocker locker(mt);
		objects.push(_object);
	}
};