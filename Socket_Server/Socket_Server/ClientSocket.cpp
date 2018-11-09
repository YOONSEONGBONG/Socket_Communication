#include "stdafx.h"
#include "ClientSocket.h"
#include "Socket_Server.h"
#include "ListenSocket.h"
#include "Socket_ServerDlg.h"


CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수
void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}
// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	CString strTmp = _T(""), strIPAddress = _T(""), str;
	UINT uPortNumber = 0;
	TCHAR strBuffer[1024];
	::ZeroMemory(strBuffer, sizeof(strBuffer)); // :: 붙이고 안붙이고 차이 알아보기
	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // 전달된 데이터(문자열)가 있을 경우	
		CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd();
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		for (int i = 0; i < sizeof(strBuffer); i++)
		{
			str += strBuffer[i];
			if (strBuffer[i] == _T(''))
			{
			break;
			}
		}
		pServerSocket->strIPAddress = strIPAddress;
		pServerSocket->uPortNumber = uPortNumber;
		if (str.Left(3) == "ID:")
		{
			str.Delete(0, 3);
			pServerSocket->client_Id = str;
			
		}
		else
		{
			CTime time = CTime::GetCurrentTime();
			pServerSocket->time = time;
			pServerSocket->pszMessage=strBuffer;
			pServerSocket->SendAllMessage();
			//CString strTimeData = t1.Format(_T(" % 04Y - % 02m - % 02d % 02H: % 02M : % 02S"));
			//strTmp.Format(_T("[%s:%d %S]: %s"), strIPAddress, strTimeData, uPortNumber, strBuffer);
			//pMain->m_List.AddString(strTmp);  // 메시지 리스트(메시지창?)에 입력받은 메시지 띄우기
			//pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
			//pServerSocket->SendAllMessage(strBuffer,time); // 다른 클라이언트들에게 메시지 전달
			
		}
		
	}

	CSocket::OnReceive(nErrorCode);
}