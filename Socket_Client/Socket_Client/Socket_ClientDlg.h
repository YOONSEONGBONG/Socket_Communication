
// Socket_ClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ConectSocket.h"


// CSocket_ClientDlg ��ȭ ����
class CSocket_ClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSocket_ClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CConectSocket m_Socket;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SOCKET_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	int LogIn_flag = 0; //0:�α��� �ȵ�,1:�α��� ��

	void Login();
	void Logout();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
