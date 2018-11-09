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


// CClientSocket ��� �Լ�
void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}
// CClientSocket ��� �Լ�


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
	::ZeroMemory(strBuffer, sizeof(strBuffer)); // :: ���̰� �Ⱥ��̰� ���� �˾ƺ���
	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // ���޵� ������(���ڿ�)�� ���� ���	
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
			//pMain->m_List.AddString(strTmp);  // �޽��� ����Ʈ(�޽���â?)�� �Է¹��� �޽��� ����
			//pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
			//pServerSocket->SendAllMessage(strBuffer,time); // �ٸ� Ŭ���̾�Ʈ�鿡�� �޽��� ����
			
		}
		
	}

	CSocket::OnReceive(nErrorCode);
}