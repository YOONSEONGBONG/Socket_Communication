#pragma once
#include "afxsock.h"
class CConectSocket :
	public CSocket
{
public:
	CConectSocket();
	~CConectSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);


};

