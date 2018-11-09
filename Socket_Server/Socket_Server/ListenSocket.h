#pragma once
#include "afxsock.h"


class CListenSocket :
	public CAsyncSocket
{
public:

	CListenSocket();
	virtual ~CListenSocket();

	CPtrList m_ptrClientSocketList;
	void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendAllMessage();


public:
	CString client_Id;
	CString strIPAddress;
	UINT uPortNumber;
	CString leave_msg = _T("´Ô ¶°³µ½À´Ï´Ù.");
	TCHAR* pszMessage;
	CTime time;
};

