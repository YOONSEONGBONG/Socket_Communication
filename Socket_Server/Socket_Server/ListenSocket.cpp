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



// CListenSocket 멤버 함수
void CListenSocket::OnAccept(int nErrorCode)
{
	
	CClientSocket* pClient = new CClientSocket;
	
	CString str = _T("");

	if (Accept(*pClient) ) { // 클라이언트 접속 요청이 오면 서버-클라이언트를 연결시켜준다
		pClient->SetListenSocket(this);
			m_ptrClientSocketList.AddTail(pClient);
			
			CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd(); // CSocketServerDlg의 핸들을 가져옴
			pClient->OnReceive(nErrorCode);
			str.Format(_T("%s[%s:%d]"), client_Id, strIPAddress, uPortNumber);
			pMain->clientList->AddString(str); // 클라이언트가 접속할때마다 리스트에 클라이언트 이름 추가
		
	}
	else {
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

// 클라이언트 연결 종료함수
void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);

	if (pos != NULL) {
		if (pClient != NULL) {
			// 클라이언트 연결중지후 종료
			pClient->ShutDown();
			pClient->Close();
		}

		CSocket_ServerDlg* pMain = (CSocket_ServerDlg*)AfxGetMainWnd();
		CString str1, str2,str3;
		UINT indx = 0, posNum;
		pMain->clientList->SetCurSel(0);
		// 접속 종료되는 클라이언트 찾기
		while (indx < pMain->clientList->GetCount()) {
			posNum = (int)m_ptrClientSocketList.Find(pClient);
			pMain->clientList->GetText(indx, str1);
			str2.Format(_T("%s[%s:%d]"), client_Id, strIPAddress, uPortNumber);
			// 소켓리스트, 클라이언트리스트를 비교해서 같은 클라이언트 번호(POSITION 값) 있으면 리스트에서 삭제
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
		pMain->m_List.AddString(strTmp);  // 메시지 리스트(메시지창?)에 입력받은 메시지 띄우기
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
			pMain->m_List.InsertString(-1, strTmp);  // 메시지 리스트(메시지창?)에 입력받은 메시지 띄우기	
			
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
			// Send함수의 두번째 인자는 메모리의 크기인데 유니코드를 사용하고 있으므로 *2를 한 크기가 된다.
			// 이 함수는 전송한 데이터의 길이를 반환한다.
			int checkLenOfData = pClient->Send(clientMsg, lstrlen(clientMsg) * 2);
			if (checkLenOfData != lstrlen(clientMsg) * 2) {
				AfxMessageBox(_T("일부 데이터가 정상적을 전송되지 못했습니다!"));
			}
			
		}
	}
}