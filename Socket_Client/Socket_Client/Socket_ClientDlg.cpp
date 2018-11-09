
// Socket_ClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Socket_Client.h"
#include "Socket_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSocket_ClientDlg 대화 상자



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


// CSocket_ClientDlg 메시지 처리기

BOOL CSocket_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_EDIT_IPADDRESS, _T("127.0.0.1"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSocket_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSocket_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSocket_ClientDlg::OnBnClickedButton1()
{
	CString str,str2;
	GetDlgItemText(IDC_EDIT_NICKNAME, str);
	
	// 방법1, 리소스뷰에서 만든 거 그대로 쓸때
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT1, str2);
	str.Append(L" : ");
	str.Append(str2);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	str2.Format(_T(""));
	SetDlgItemText(IDC_EDIT1, str2);
	UpdateData(FALSE);
	
	/*
	// 방법2. 객체생성해서 쓸때
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
