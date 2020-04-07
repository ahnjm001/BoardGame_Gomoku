#pragma once

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <process.h>

#include <map>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>

#include "packet.h"

#include "IOCPClass.h"

using namespace std;

#define IOCPCLASS IOCPClass::getSingleton()

#define SAFE_DELETE(p)			{ if (p) { delete (p); (p) = NULL; } }
#define	SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p); (p) = NULL;} }

/*
// new (new char)�� ������ �޸� p�� ���� �մϴ�.
#define SAFE_DELETE( p ) { if( p ) { delete ( p ); ( p ) = NULL; } }

// new (new char *) �� ������ �迭 p�� ���� �մϴ�.
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p ); ( p ) = NULL; } }
*/