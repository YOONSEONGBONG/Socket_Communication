
// Socket_ClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ConectSocket.h"


// CSocket_ClientDlg 대화 상자
class CSocket_ClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CConectSocket m_Socket;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonLogin();
	CString IP_Address;
	CString Id;
	CEdit CIpaddress;
	CEdit CId;
	afx_msg void OnBnClickedButtonLogout();
	int LogIn_flag = 0; //0:로그인 안됨,1:로그인 됨

	void Login();
	void Logout();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
