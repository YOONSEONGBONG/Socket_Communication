#include "stdafx.h"
#include "ConectSocket.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"


CConectSocket::CConectSocket()
{
}


CConectSocket::~CConectSocket()
{
}

// CConectSocket ¸â¹ö ÇÔ¼ö


void CConectSocket::OnClose(int nErrorCode)
{

	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR:Disconnected from server!"));
	CSocket_ClientDlg * client = (CSocket_ClientDlg*)AfxGetMainWnd();
	client->LogIn_flag = 0;
	//¼­¹ö Æ¨±è
	client->Login();
	//::PostQuitMessage(0);

}

void CConectSocket::OnReceive(int nErrorCode)
{
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0) {
		CSocket_ClientDlg* pMain = (CSocket_ClientDlg*)AfxGetMainWnd();
		pMain->m_List.AddString(szBuffer);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	}
	CSocket::OnReceive(nErrorCode);
}