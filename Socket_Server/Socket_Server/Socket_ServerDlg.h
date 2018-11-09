
// Socket_ServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CSocket_ServerDlg ��ȭ ����
class CSocket_ServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSocket_ServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CListenSocket m_ListenSocket;
	CListBox* clientList;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SOCKET_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	void OnDestroy();

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
	int start_flag = 0;


	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};