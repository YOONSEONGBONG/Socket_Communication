
// Socket_Client.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSocket_ClientApp:
// �� Ŭ������ ������ ���ؼ��� Socket_Client.cpp�� �����Ͻʽÿ�.
//

class CSocket_ClientApp : public CWinApp
{
public:
	CSocket_ClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSocket_ClientApp theApp;