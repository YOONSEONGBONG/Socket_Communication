
// Socket_Server.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSocket_ServerApp:
// �� Ŭ������ ������ ���ؼ��� Socket_Server.cpp�� �����Ͻʽÿ�.
//

class CSocket_ServerApp : public CWinApp
{
public:
	CSocket_ServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSocket_ServerApp theApp;