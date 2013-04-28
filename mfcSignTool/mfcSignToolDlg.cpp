
// mfcSignToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "mfcSignToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmfcSignToolDlg �Ի���




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


// CmfcSignToolDlg ��Ϣ�������

BOOL CmfcSignToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	m_hIcon=AfxGetApp()->LoadIcon(IDI_SEAL);
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//Initialize the winsock lib
	WSADATA wsaData;
	WORD sockVersion=MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	
	//��ʼ��״̬��
	m_bar.EnableAutomation();
	m_bar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,0);
	int nWidth[]={200,350,-1};
	m_bar.SetParts(3,nWidth);
	m_bar.SetText(L"����״̬: ��δ��ǩ������������",0,0);
	m_bar.SetText(L"��ǰģʽ:  ǩ������ģʽ",0,1);
	
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
		CString csIp("����IP:  ");
		csIp+=wcHostIp;
		m_bar.SetText(csIp,0,2);
	}
	else
	{
		m_bar.SetText(L"����IP: ��ȡʧ��.",0,2);
	}
	//��ʼ����ťicon
	m_hIconOn=AfxGetApp()->LoadIconW(IDI_ICON_ON);
	m_hIconOff=AfxGetApp()->LoadIconW(IDI_ICON_OFF);
	m_btnSideAsk.SetIcon(m_hIconOn);
	SetDlgItemTextW(IDC_BTN_SIDE_ASK,L"ǩ������ģʽ");
	m_btnSideSign.SetIcon(m_hIconOff);
	SetDlgItemTextW(IDC_BTN_SIDE_SIGN,L"ǩ��ģʽ");
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcSignToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfcSignToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CmfcSignToolDlg::OnBnClickedBtnSideAsk()
{
	//set bar
	m_bar.SetText(L"��ǰģʽ: ǩ������ģʽ",0,1);
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
	m_bar.SetText(L"��ǰģʽ: ǩ��ģʽ",0,1);
	//change icon
	m_btnSideAsk.SetIcon(m_hIconOff);
	m_btnSideSign.SetIcon(m_hIconOn);
	//enable m_dlgServer and disable m_dlgClient
	m_dlgClient.EnableWindow(false);
	m_dlgClient.ShowWindow(false);
	m_dlgServer.EnableWindow(true);
	m_dlgServer.ShowWindow(true);
}
