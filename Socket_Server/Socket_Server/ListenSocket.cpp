#include "stdafx.h"
#include "ListenSocket.h"
#include "Socket_Server.h"
#include "ClientSocket.h"
#include "Socket_ServerDlg.h"


CListenSocket::CListenSocket()
{
}


CListenSocket::~CListenSocket()
{
}



// CListenSocket ��� �Լ�
void CListenSocket::OnAccept(int nErrorCode)
{
	
	CClientSocket* pClient = new CClientSocket;
	
	CString str = _T("");

	if (Accept(*pClient) ) { // Ŭ���̾�Ʈ ���� ��û�� ���� ����-Ŭ���̾�Ʈ�� ��������ش�
		pClient->SetListenSocket(this);
			m_ptrClientSocketList.AddTail(pClient);
			
			CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd(); // CSocketServerDlg�� �ڵ��� ������
			pClient->OnReceive(nErrorCode);
			str.Format(_T("%s[%s:%d]"), client_Id, strIPAddress, uPortNumber);
			pMain->clientList->AddString(str); // Ŭ���̾�Ʈ�� �����Ҷ����� ����Ʈ�� Ŭ���̾�Ʈ �̸� �߰�
		
	}
	else {
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

// Ŭ���̾�Ʈ ���� �����Լ�
void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);

	if (pos != NULL) {
		if (pClient != NULL) {
			// Ŭ���̾�Ʈ ���������� ����
			pClient->ShutDown();
			pClient->Close();
		}

		CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd();
		CString str1, str2,str3;
		UINT indx = 0, posNum;
		pMain->clientList->SetCurSel(0);
		// ���� ����Ǵ� Ŭ���̾�Ʈ ã��
		while (indx < pMain->clientList->GetCount()) {
			posNum = (int)m_ptrClientSocketList.Find(pClient);
			pMain->clientList->GetText(indx, str1);
			str2.Format(_T("%s[%s:%d]"), client_Id, strIPAddress, uPortNumber);
			// ���ϸ���Ʈ, Ŭ���̾�Ʈ����Ʈ�� ���ؼ� ���� Ŭ���̾�Ʈ ��ȣ(POSITION ��) ������ ����Ʈ���� ����
			if (str1==str2) {
				pMain->clientList->DeleteString(indx);
				break;
			}
			indx++;
		}

		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

void CListenSocket::SendAllMessage()
{
	CString strTmp,str1,str2,str3,str4;
	TCHAR* clientMsg=_T("");
	CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd();
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	TCHAR* pID = (TCHAR*)pos;

	CString strTimeData = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	strTmp.Format(_T("[%s:%d %s]: %s"), strIPAddress, uPortNumber, strTimeData, pszMessage);
	str3.Format(_T("[%s]"), strTimeData);
	if (pMain->m_List.GetCount() == 0)
	{
		pMain->m_List.AddString(strTmp);  // �޽��� ����Ʈ(�޽���â?)�� �Է¹��� �޽��� ����
		str3+=strTmp.Right(strTmp.GetLength() - strTmp.Find(_T(": "))).Trim(_T(": "));
		clientMsg = (TCHAR*)(LPCTSTR)str3;
	}
	else
	{
		pMain->m_List.GetText(pMain->m_List.GetCount()-1, str1);
		str2=str1.Mid(str1.Find(_T(" ")), 20);
		int nYear = _ttoi(str2.Left(5));
		int nMon = _ttoi(str2.Mid(6, 2));
		int nDay = _ttoi(str2.Mid(9, 2));
		int nHour = _ttoi(str2.Mid(12, 2));
		int nMin = _ttoi(str2.Mid(15, 2));
		int nSec = _ttoi(str2.Mid(18, 2));

		CTime tiTime(nYear, nMon, nDay, nHour, nMin, nSec);

		if (time > tiTime)
		{
			pMain->m_List.InsertString(-1, strTmp);  // �޽��� ����Ʈ(�޽���â?)�� �Է¹��� �޽��� ����	
			
			str3 += strTmp.Right(strTmp.GetLength() - strTmp.Find(_T(": "))).Trim(_T(": "));
			clientMsg = (TCHAR*)(LPCTSTR)str3;
		}
	}
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	/*
	str3.Format(_T("%s"),pszMessage);
	str4 = str1.Right(str1.GetLength()-str1.Find(_T(": "))).Trim(_T(": "));
	if (str3 == str4)
	{
		clientMsg = pszMessage;
	}
	clientMsg = (TCHAR*)(LPCTSTR)str4;
	*/
	while (pos != NULL) {
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL) {
			// Send�Լ��� �ι�° ���ڴ� �޸��� ũ���ε� �����ڵ带 ����ϰ� �����Ƿ� *2�� �� ũ�Ⱑ �ȴ�.
			// �� �Լ��� ������ �������� ���̸� ��ȯ�Ѵ�.
			int checkLenOfData = pClient->Send(clientMsg, lstrlen(clientMsg) * 2);
			if (checkLenOfData != lstrlen(clientMsg) * 2) {
				AfxMessageBox(_T("�Ϻ� �����Ͱ� �������� ���۵��� ���߽��ϴ�!"));
			}
			
		}
	}
}