
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
	ON_COMMAND(ID_SHUTSERV, &CmfcSignToolDlg::OnShutserv)
	ON_COMMAND(ID_OPENSERV, &CmfcSignToolDlg::OnOpenserv)
	ON_COMMAND(ID_MENU_SHUTCONN, &CmfcSignToolDlg::OnMenuShutconn)
	ON_COMMAND(ID_CONNSVR, &CmfcSignToolDlg::OnConnsvr)
	ON_COMMAND(ID_MENU_OPENFILE, &CmfcSignToolDlg::OnMenuOpenfile)
	ON_COMMAND(ID_MENU_OUTVAR, &CmfcSignToolDlg::OnMenuOutvar)
	ON_COMMAND(ID_MENU_EXIT, &CmfcSignToolDlg::OnMenuExit)
	ON_COMMAND(ID_MENU_ASKMODE, &CmfcSignToolDlg::OnMenuAskmode)
	ON_COMMAND(ID_MENU_SIGN_MODE, &CmfcSignToolDlg::OnMenuSignMode)
	ON_COMMAND(ID_MENU_DEMO, &CmfcSignToolDlg::OnMenuDemo)
	ON_COMMAND(ID_MENU_RSAVAR, &CmfcSignToolDlg::OnMenuRsavar)
	ON_COMMAND(ID_MENU_PEERINFO, &CmfcSignToolDlg::OnMenuPeerInfo)
	ON_COMMAND(ID_MENU_SELFINFO, &CmfcSignToolDlg::OnMenuSelfinfo)
	ON_COMMAND(ID_MENU_BSIGN, &CmfcSignToolDlg::OnMenuBSign)
	ON_COMMAND(ID_MENU_SOCKVAR, &CmfcSignToolDlg::OnMenuSockvar)
	ON_COMMAND(ID_MENU_SETRSAVAR, &CmfcSignToolDlg::OnMenuSetRsaVar)
	ON_COMMAND(ID_MENU_SETBSVAR, &CmfcSignToolDlg::OnMenuSetbsvar)
	ON_COMMAND(ID_MENU_SETSOCKVAR, &CmfcSignToolDlg::OnMenuSetsockvar)
	ON_COMMAND(ID_32793, &CmfcSignToolDlg::On32793)
	ON_COMMAND(ID_32794, &CmfcSignToolDlg::On32794)
	ON_COMMAND(ID_MENU_CLIENTLIST, &CmfcSignToolDlg::OnMenuClientList)
	ON_COMMAND(ID_32783, &CmfcSignToolDlg::OnHowToUse)
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
	//Initialize the value of class members
	m_bSignMode=false;

	//Initialize the winsock lib
	WSADATA wsaData;
	WORD sockVersion=MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	
	//��ʼ��״̬��
	m_bar.EnableAutomation();
	m_bar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,0);
	int nWidth[]={230,370,-1};
	m_bar.SetParts(3,nWidth);
	m_bar.SetText(L"�����Ϣ:  (�˵����)",0,0);
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
	m_bSignMode=false;
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
	m_bSignMode=true;
	//change icon
	m_btnSideAsk.SetIcon(m_hIconOff);
	m_btnSideSign.SetIcon(m_hIconOn);
	//enable m_dlgServer and disable m_dlgClient
	m_dlgClient.EnableWindow(false);
	m_dlgClient.ShowWindow(false);
	m_dlgServer.EnableWindow(true);
	m_dlgServer.ShowWindow(true);
}


void CmfcSignToolDlg::OnShutserv()
{
	//call CServerDlg to shut service down
	//�����жϷ����Ƿ���
	if(m_bSignMode && m_dlgServer.m_bService)
	{
		m_dlgServer.CloseAllSocket();
		m_dlgServer.m_bService=false;
		m_dlgServer.GetDlgItem(IDC_BTN_OPENSERV)->EnableWindow(true);
		m_dlgServer.GetDlgItem(IDC_BTN_RANDGEN)->EnableWindow(true);
	}
	else
		if(m_bSignMode)
			m_bar.SetText(L"�����Ϣ:  ����û�п���,̸�ιر�.",0,0);
		else
			m_bar.SetText(L"�����Ϣ:  ��ǰģʽ����ǩ��ģʽ,��ô.",0,0);
}


void CmfcSignToolDlg::OnOpenserv()
{
	//first judge if service is ON
	if(m_bSignMode && !m_dlgServer.m_bService)
	{
		//don't forget to set m_bService
		m_dlgServer.OnBnClickedBtnOpenserv();
		m_dlgServer.m_bService=true;
	}
	else
	{
		if(m_bSignMode)
			m_bar.SetText(L"�����Ϣ:  �����Ѿ�������,��ô.",0,0);
		else
			m_bar.SetText(L"�����Ϣ:  ��ǰģʽ����ǩ��ģʽ,��ô.",0,0);
	}
}


void CmfcSignToolDlg::OnMenuShutconn()
{
	//shut the connection down(works for client/SideAsk mode)
	if(!m_bSignMode)
		m_dlgClient.ShutConn();
	else
		m_bar.SetText(L"�����Ϣ:  ��ǰģʽ��ǩ��ģʽ,��ô.",0,0);
}


void CmfcSignToolDlg::OnConnsvr()
{
	//first judge the current mode
	if(!m_bSignMode && !m_dlgClient.m_bConnect)
	{
		//pop up the ConnSvr dlg
		if(IDOK == m_dlgConnSvr.DoModal())
		{
			m_dlgClient.m_barClient.SetText(L"����״̬:  ��������..",0,0);
			m_dlgClient.CreateAndConn(m_dlgConnSvr.m_szIpSvr,m_dlgConnSvr.m_nPort);
		}
		//clear client RecvState EditCtrl
		m_dlgClient.SetDlgItemTextW(IDC_E_RECVSTATE,L"");
		m_dlgClient.SetDlgItemTextW(IDC_E_UNBLIND,L"");
		m_dlgClient.SetDlgItemTextW(IDC_E_VERIFY,L"");
	}
	else if(m_bSignMode)
		MessageBox(L"��ǰģʽ����ǩ������ģʽ!",L"����",MB_OK);
	else if(m_dlgClient.m_bConnect)
		MessageBox(L"�Ѿ���ǩ��������������.",L"����",MB_OK);
}


void CmfcSignToolDlg::OnMenuOpenfile()
{
	//PROXY
	m_dlgClient.OnBnClickedBtnOpenfile();
}


void CmfcSignToolDlg::OnMenuOutvar()
{
	//E,D,N,P,Q;only for SERVER
	if(!m_bSignMode)
	{
		MessageBox(L"ֻ��ǩ������Ȩ�޵�������!",L"����",MB_OK);
		return;
	}
	//�����������ļ�
	wchar_t szSaveFile[MAX_PATH]={0};//������Ҫ��ȡҪ���ܵ��ļ���+�������ܣ���
	OPENFILENAME SaveFile={0};
	SaveFile.lStructSize=sizeof(OPENFILENAME);
	SaveFile.lpstrFile=szSaveFile;
	SaveFile.nMaxFile=MAX_PATH;
	SaveFile.lpstrFilter=L"Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	SaveFile.lpstrDefExt=L".txt";
	SaveFile.nFilterIndex=1;
	SaveFile.Flags=OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT;
	if(::GetSaveFileName(&SaveFile))
	{
		//�����ж��Ƿ�ɵ�����Чֵ
		if(m_dlgServer.m_rsaE.IsZero()||m_dlgServer.m_rsaD.IsZero()||m_dlgServer.m_rsaN.IsZero())
		{
			MessageBox(L"��Կ��(e,d)����������Ϊ0!",L"����",MB_OK);
			return;
		}
		//������д�뵽�ļ�
		ofstream fout(szSaveFile,ios::out);
		fout.clear();
		fout<<"--------RSA Related-------------------\n";
		fout<<"p: "<<hex<<m_dlgServer.m_rsaP<<"\n";
		fout<<"q: "<<hex<<m_dlgServer.m_rsaQ<<"\n";
		fout<<"n: "<<hex<<m_dlgServer.m_rsaN<<"\n";
		fout<<"e: "<<hex<<m_dlgServer.m_rsaE<<"\n";
		fout<<"d: "<<hex<<m_dlgServer.m_rsaD<<"\n";
		fout<<"--------RSA Related-------------------\n";
		fout.close();
		MessageBox(L"���������ɹ�!",L"����",MB_OK);
	}
}


void CmfcSignToolDlg::OnMenuExit()
{
	CDialog::OnOK();
}


void CmfcSignToolDlg::OnMenuAskmode()
{
	OnBnClickedBtnSideAsk();
}


void CmfcSignToolDlg::OnMenuSignMode()
{
	OnBnClickedBtnSideSign();
}


void CmfcSignToolDlg::OnMenuDemo()
{
	//first check if mfcBlindSignP.exe EXISTS
	fstream file("mfcBlindSignP.exe",ios::in);
	if(!file)
	{
		MessageBox(L"û���ҵ�ԭ����ʾ����!",L"����",MB_OK);
		return;
	}
	//system("mfcBlindSignP.exe");
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = L"mfcBlindSignP.exe"; //can be a file as well
	ShExecInfo.lpParameters = L"";
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
}


void CmfcSignToolDlg::OnMenuRsavar()
{
	if(!m_bSignMode)
	{
		MessageBox(L"ֻ��ǩ������Ȩ�޲鿴RSA����!",L"����",MB_OK);
		return;
	}
	//Integer-->char(m_szE,m_szN is available)
	stringstream sstream;
	char szP[MAX_HEX_DIGITS]={0};
	sstream<<hex<<m_dlgServer.m_rsaP;
	sstream>>szP;
	char szQ[MAX_HEX_DIGITS]={0};
	sstream.clear();
	sstream<<hex<<m_dlgServer.m_rsaQ;
	sstream>>szQ;
	char szD[MAX_HEX_DIGITS]={0};
	sstream.clear();
	sstream<<hex<<m_dlgServer.m_rsaD;
	sstream>>szD;
	//convery the value to RsaVarDlg
	CRsaVarDlg dlg;
	dlg.SetUiText(szP,szQ,m_dlgServer.m_szN,m_dlgServer.m_szE,szD);
	dlg.DoModal();
}


void CmfcSignToolDlg::OnMenuPeerInfo()
{
	//only apply to CLIENT mode;if server,should use "ClientList" menu
	if(m_bSignMode)
	{
		MessageBox(L"�ð�ťֻ��ǩ��������Ч;\nǩ��������\"�ͻ��б�\"",L"����",MB_OK);
		return;
	}
	//only work when CONNECTED
	if(!m_dlgClient.m_bConnect)
	{
		MessageBox(L"��Ǹ,����û�����ӵ�ǩ����..",L"����",MB_OK);
		return;
	}
	//
	sockaddr_in sinServer;
	int nSinLen=sizeof(sinServer);
	memset(&sinServer,0,nSinLen);
	::getpeername(m_dlgClient.m_sockClient,(sockaddr*)&sinServer,&nSinLen);
	//��ȡ�����ֽ�˳��Ķ˿ں�
	int nPeerPort=::ntohs(sinServer.sin_port);
	char szPeerPort[10]={0};
	itoa(nPeerPort,szPeerPort,10);//3rd argu:radix
	//��ȡ�����ֽ�˳���IP
	char* pchPeerIp=new char[20];
	pchPeerIp=::inet_ntoa(sinServer.sin_addr);
	//--��ȡ�Է���������--
	//��ȡ�����ֽ�˳���char ip
	DWORD dwIp=::inet_addr(pchPeerIp);
	HOSTENT* pHost=::gethostbyaddr((LPSTR)&dwIp,4,AF_INET);
	char szHostName[50]={0};
	memcpy(szHostName,pHost->h_name,50);
	//--��ȡ�Է�����������--
	//popup the PeerInfoDlg
	CPeerInfoDlg dlg;
	dlg.setUiText(pchPeerIp,szPeerPort,szHostName);
	dlg.DoModal();
}


void CmfcSignToolDlg::OnMenuSelfinfo()
{
	//stream<<system("hostname");
	//replace dlg with the simplest MessageBox
	//already have: m_szHostIp, m_szHostName
    sockaddr_in sinLocal;
	int nSinLen=sizeof(sinLocal);
	if(m_bSignMode)
		::getsockname(m_dlgServer.m_sockServer,(sockaddr*)&sinLocal,&nSinLen);
	else
		::getsockname(m_dlgClient.m_sockClient,(sockaddr*)&sinLocal,&nSinLen);
	//get addr family type;MUST be AF_INET
	short nAddrType=sinLocal.sin_family;
	char szAddrType[10]={0};
	if(nAddrType==2)
		memcpy(szAddrType,"AF_INET",10);
	else
		memcpy(szAddrType,"(δ����)",10);
	//get the binding port
	char szPort[10]={0};
	unsigned short nPort=sinLocal.sin_port;
	itoa(nPort,szPort,10);
	//combine together
	CString csTmp;
	csTmp+="��ַ����:  ";
	csTmp+=szAddrType;
	csTmp+="\n";
	csTmp+="����IP:    ";
	csTmp+=m_szHostIp;
	csTmp+="\n";
	csTmp+="ʹ�ö˿�:  ";
	csTmp+=szPort;
	csTmp+="\n";
	csTmp+="������:    ";
	csTmp+=m_szHostName;
	MessageBox(csTmp,L"������Ϣ",MB_OK);
}


void CmfcSignToolDlg::OnMenuBSign()
{
	//only work in CLIENT mode
	if(m_bSignMode)
	{
		MessageBox(L"ǩ������Ȩ��!",L"����",MB_OK);
		return;
	}
	//show Bind Func and Blind Factor k
	stringstream sstream;
	sstream<<hex<<m_dlgClient.m_nK;
	char szK[10]={0};
	sstream>>szK;
	CString csTmp;
	csTmp+="ä������:  ��ϢժҪ(MD5)\n";
	csTmp+="ä������:  ";
	csTmp+=szK;
	MessageBox(csTmp,L"äǩ����ز���",MB_OK);
}


void CmfcSignToolDlg::OnMenuSockvar()
{
	//m_nBackLog m_nMaxSocket;only work in SERVER mode 
	if(!m_bSignMode)
	{
		MessageBox(L"ǩ������û�д���Ϣ.",L"ERROR",MB_OK);
		return;
	}
	char szBacklog[5]={0};
	itoa(m_dlgServer.m_nBacklog,szBacklog,10);
	char szMaxClient[5]={0};
	itoa(m_dlgServer.m_nMaxSocket,szMaxClient,10);
	CString csTmp;
	csTmp+="backlog:     ";
	csTmp+=szBacklog;
	csTmp+="\n";
	csTmp+="���������:  ";
	csTmp+="56\n";
	csTmp+="ʹ�ö˿�:    ";
	char szPort[10]={0};
	itoa(m_dlgServer.m_nPort,szPort,10);
	csTmp+=szPort;
	MessageBox(csTmp,L"WinSock�����Ϣ",MB_OK);
}


void CmfcSignToolDlg::OnMenuSetRsaVar()
{
	if(!m_bSignMode)
	{
		MessageBox(L"ǩ��������Ȩ��!",L"ERROR",MB_OK);
		return;
	}
	CSetRsaVarDlg dlg;
	if(IDOK == dlg.DoModal())
	{
		//(e,d)already validate
		m_dlgServer.m_rsaE=dlg.m_intSetE;
		m_dlgServer.m_rsaD=dlg.m_intSetD;
		m_dlgServer.m_rsaN=dlg.m_intSetN;
		//����˳����Ҳ��ֵ��m_dlgServer.m_szE/N
		//disp on UI
		char szTmp[MAX_HEX_DIGITS]={0};
		wchar_t wszTmp[MAX_HEX_DIGITS]={0};
		stringstream sstream;
		sstream<<hex<<dlg.m_intSetE;
		sstream>>szTmp;
		memcpy(m_dlgServer.m_szE,szTmp,MAX_HEX_DIGITS);
		MultiByteToWideChar(CP_ACP,0,szTmp,-1,wszTmp,MAX_HEX_DIGITS);
		m_dlgServer.SetDlgItemTextW(IDC_E_PUB,wszTmp);

		sstream.clear();
		memset(szTmp,0,MAX_HEX_DIGITS);
		memset(wszTmp,0,MAX_HEX_DIGITS);
		sstream<<hex<<dlg.m_intSetD;
		sstream>>szTmp;
		MultiByteToWideChar(CP_ACP,0,szTmp,-1,wszTmp,MAX_HEX_DIGITS);
		m_dlgServer.SetDlgItemTextW(IDC_E_PRIV,wszTmp);

		sstream.clear();
		memset(szTmp,0,MAX_HEX_DIGITS);
		sstream<<hex<<dlg.m_intSetN;
		sstream>>szTmp;
		memcpy(m_dlgServer.m_szN,szTmp,MAX_HEX_DIGITS);

		sstream.clear();
	}
}


void CmfcSignToolDlg::OnMenuSetbsvar()
{
	if(m_bSignMode)
	{
		MessageBox(L"ǩ������Ȩ��!",L"ERROR",MB_OK);
		return;
	}
	CSetBsVarDlg dlg;
	if(IDOK == dlg.DoModal())
	{
		m_dlgClient.m_nK=dlg.m_nSetK;
	}
}


void CmfcSignToolDlg::OnMenuSetsockvar()
{
	//only work in SERVER mode
	if(!m_bSignMode)
	{
		MessageBox(L"ǩ��������������!",L"ERROR",MB_OK);
		return;
	}
	CSetSockVarDlg dlg;
	if(IDOK==dlg.DoModal())
	{
		m_dlgServer.m_nBacklog=dlg.m_nSetBacklog;
		m_dlgServer.m_nMaxSocket=dlg.m_nSetMaxClient;
		m_dlgServer.m_nPort=dlg.m_nSetPort;
	}
}


void CmfcSignToolDlg::On32793()
{
	CMd5ToolDlg* pDlg=new CMd5ToolDlg;
	pDlg->Create(IDD_DLG_MD5TOOL,this);
	pDlg->ShowWindow(true);
}


void CmfcSignToolDlg::On32794()
{
	CAesToolDlg* pDlg=new CAesToolDlg;
	pDlg->Create(IDD_DLG_AESTOOL,this);
	pDlg->ShowWindow(true);
}


void CmfcSignToolDlg::OnMenuClientList()
{
	if(!m_bSignMode)
	{
		MessageBox(L"ǩ�������޴�����!",L"ERROR",MB_OK);
		return;
	}

	CClientListDlg* pDlg=new CClientListDlg;
	//clear vector before using it
	(pDlg->m_vecClient).clear();
	//using m_dlgServer.m_arClient
	int nLen=m_dlgServer.m_nClient;

	for(int i=0;i<nLen;i++)
	{
		//peer�Է���IP���˿ںš�������
		sockaddr_in sinClient;
		int nSinLen=sizeof(sinClient);
		memset(&sinClient,0,nSinLen);
		::getpeername(m_dlgServer.m_arClient[i],(sockaddr*)&sinClient,&nSinLen);
		//��ȡ�����ֽ�˳��Ķ˿ں�
		int nPeerPort=::ntohs(sinClient.sin_port);
		char szPeerPort[10]={0};
		wchar_t wszPeerPort[20]={0};
		itoa(nPeerPort,szPeerPort,10);//3rd:radix
		MultiByteToWideChar(CP_ACP,0,szPeerPort,-1,wszPeerPort,10);
		//��ȡ�����ֽ�˳���IP
		char* szPeerIp=new char[20];
		wchar_t wszPeerIp[40]={0};
		szPeerIp=::inet_ntoa(sinClient.sin_addr);
		MultiByteToWideChar(CP_ACP,0,szPeerIp,-1,wszPeerIp,20);
		//--��ȡ�Է���������--
		//��ȡ�����ֽ�˳���char ip
		DWORD dwIp=::inet_addr(szPeerIp);
		HOSTENT* pHost=::gethostbyaddr((LPSTR)&dwIp,4,AF_INET);
		char szHostName[50]={0};
		wchar_t wszHostName[100]={0};
		memcpy(szHostName,pHost->h_name,50);
		MultiByteToWideChar(CP_ACP,0,szHostName,-1,wszHostName,50);

		//give values to ClientListDlg
		pDlg->SetListVec(L"AF_INET",wszPeerIp,wszPeerPort,wszHostName);
		
	}

	pDlg->Create(IDD_DLG_CLIENTLIST,this);
	pDlg->ShowWindow(true);
}


void CmfcSignToolDlg::OnHowToUse()
{
	CHowDlg* pDlg=new CHowDlg;
	pDlg->Create(IDD_DLG_HOW,this);
	pDlg->ShowWindow(true);
}
