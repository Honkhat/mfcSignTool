
// mfcSignToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "mfcSignToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedBtnSideAsk();
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


// CmfcSignToolDlg 对话框




CmfcSignToolDlg::CmfcSignToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcSignToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcSignToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//hj added handly
	DDX_Control(pDX,IDC_BTN_SIDE_ASK,m_btnSideAsk);
	DDX_Control(pDX,IDC_BTN_SIDE_SIGN,m_btnSideSign);
}

BEGIN_MESSAGE_MAP(CmfcSignToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SIDE_ASK, &CmfcSignToolDlg::OnBnClickedBtnSideAsk)
	ON_BN_CLICKED(IDC_BTN_SIDE_SIGN, &CmfcSignToolDlg::OnBnClickedBtnSideSign)
END_MESSAGE_MAP()


// CmfcSignToolDlg 消息处理程序

BOOL CmfcSignToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	m_hIcon=AfxGetApp()->LoadIcon(IDI_SEAL);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//Initialize the winsock lib
	WSADATA wsaData;
	WORD sockVersion=MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	
	//初始化状态栏
	m_bar.EnableAutomation();
	m_bar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,0);
	int nWidth[]={200,350,-1};
	m_bar.SetParts(3,nWidth);
	m_bar.SetText(L"网络状态: 尚未与签名方建立连接",0,0);
	m_bar.SetText(L"当前模式:  签名请求模式",0,1);
	
	//get local IP
	memset(m_szHostName,0,256);
	memset(m_szHostIp,0,20);
	::gethostname(m_szHostName,256);
	HOSTENT* pHostent=gethostbyname(m_szHostName);
	if(pHostent!=NULL)
	{
		in_addr* addr=(in_addr*)*(pHostent->h_addr_list);
		wchar_t wcHostIp[20]={0};
		memcpy(m_szHostIp,inet_ntoa(addr[0]),20);
		MultiByteToWideChar(CP_ACP,0,m_szHostIp,-1,wcHostIp,20);
		CString csIp("本地IP:  ");
		csIp+=wcHostIp;
		m_bar.SetText(csIp,0,2);
	}
	else
	{
		m_bar.SetText(L"本地IP: 获取失败.",0,2);
	}
	//初始化按钮icon
	m_hIconOn=AfxGetApp()->LoadIconW(IDI_ICON_ON);
	m_hIconOff=AfxGetApp()->LoadIconW(IDI_ICON_OFF);
	m_btnSideAsk.SetIcon(m_hIconOn);
	SetDlgItemTextW(IDC_BTN_SIDE_ASK,L"签名请求模式");
	m_btnSideSign.SetIcon(m_hIconOff);
	SetDlgItemTextW(IDC_BTN_SIDE_SIGN,L"签名模式");
	//set default mode
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	rect.top+=10;

	m_dlgClient.Create(IDD_DLG_CLIENT,GetDlgItem(IDC_STATIC));
	m_dlgServer.Create(IDD_DLG_SERVER,GetDlgItem(IDC_STATIC));

	m_dlgClient.ShowWindow(true);
	m_dlgServer.ShowWindow(false);

	//release winsock lib
	::WSACleanup();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcSignToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcSignToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcSignToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CmfcSignToolDlg::OnBnClickedBtnSideAsk()
{
	//set bar
	m_bar.SetText(L"当前模式: 签名请求模式",0,1);
	//change icon
	m_btnSideAsk.SetIcon(m_hIconOn);
	m_btnSideSign.SetIcon(m_hIconOff);
	//enable m_dlgClient and disable m_dlgServer
	m_dlgClient.EnableWindow(true);
	m_dlgClient.ShowWindow(true);
	m_dlgServer.EnableWindow(false);
	m_dlgServer.ShowWindow(false);
}


void CmfcSignToolDlg::OnBnClickedBtnSideSign()
{
	//set bar
	m_bar.SetText(L"当前模式: 签名模式",0,1);
	//change icon
	m_btnSideAsk.SetIcon(m_hIconOff);
	m_btnSideSign.SetIcon(m_hIconOn);
	//enable m_dlgServer and disable m_dlgClient
	m_dlgClient.EnableWindow(false);
	m_dlgClient.ShowWindow(false);
	m_dlgServer.EnableWindow(true);
	m_dlgServer.ShowWindow(true);
}
