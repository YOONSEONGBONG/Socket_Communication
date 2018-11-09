
// Socket_ClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocket_ClientDlg ��ȭ ����



CSocket_ClientDlg::CSocket_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocket_ClientDlg::IDD, pParent)
	, IP_Address(_T(""))
	, Id(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocket_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS, IP_Address);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, Id);
	DDX_Control(pDX, IDC_EDIT_IPADDRESS, CIpaddress);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, CId);
}

BEGIN_MESSAGE_MAP(CSocket_ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSocket_ClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CSocket_ClientDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CSocket_ClientDlg::OnBnClickedButtonLogout)
END_MESSAGE_MAP()


// CSocket_ClientDlg �޽��� ó����

BOOL CSocket_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(IDC_EDIT_IPADDRESS, _T("127.0.0.1"));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSocket_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSocket_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocket_ClientDlg::OnBnClickedButton1()
{
	CString str,str2;
	GetDlgItemText(IDC_EDIT_NICKNAME, str);
	
	// ���1, ���ҽ��信�� ���� �� �״�� ����
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT1, str2);
	str.Append(L" : ");
	str.Append(str2);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	str2.Format(_T(""));
	SetDlgItemText(IDC_EDIT1, str2);
	UpdateData(FALSE);
	
	/*
	// ���2. ��ü�����ؼ� ����
	CEdit* test = (CEdit*)GetDlgItem(IDC_EDIT1);
	test->GetWindowTextW(str);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	test->SetWindowTextW(_T(""));
	*/
}

void CSocket_ClientDlg::Login()
{
	CString str, str2;
	int count = 0;
	while (true)
	{
		m_Socket.Create();
		if (m_Socket.Connect(IP_Address, 21000) == FALSE) {
				m_Socket.Close();
				if (count == 3)
				{	
					if (AfxMessageBox(_T("ERROR : Failed to connect Server"), MB_RETRYCANCEL)==IDRETRY)
					{
						count = 0;
					}
					else 
					{
						CIpaddress.SetReadOnly(false);
						CId.SetReadOnly(false);
						LogIn_flag = 0;
						break;
					}
				}
			//PostQuitMessage(0);
		}
		else
		{
			str = _T("ID:");
			GetDlgItemText(IDC_EDIT_NICKNAME, str2);
			AfxMessageBox(str2 + _T(" WelCome!"));
			CIpaddress.SetReadOnly(true);
			CId.SetReadOnly(true);
			str += str2;
			m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
			LogIn_flag = 1;
			break;
			
		}
		Sleep(2000);
		count++;
	}
}

void CSocket_ClientDlg::Logout()
{
	CString str;
	GetDlgItemText(IDC_EDIT_NICKNAME, str);
	m_Socket.ShutDown();
	m_Socket.Close();
	AfxMessageBox(str + _T(" ByeBye!"));
	CIpaddress.SetReadOnly(false);
	CId.SetReadOnly(false);
	LogIn_flag = 0;
}
void CSocket_ClientDlg::OnBnClickedButtonLogin()
{
	if (LogIn_flag == 0)
	{
//	m_Socket.Create();
	Login();
	}

}

void CSocket_ClientDlg::OnBnClickedButtonLogout()
{
	if (LogIn_flag == 1)
	{
		Logout();
	}
}


BOOL CSocket_ClientDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButton1();
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
