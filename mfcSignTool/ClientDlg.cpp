// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
//hj added
#define WM_SOCKET WM_USER+5

// CClientDlg 对话框

IMPLEMENT_DYNAMIC(CClientDlg, CDialogEx)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{

}

CClientDlg::~CClientDlg()
{
	//-------------!!!!!!!!!!!!!!!!!!!!!!!!--ShutConn()-----
	ShutConn();
	::WSACleanup();
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_SEND, &CClientDlg::OnBnClickedRadioSend)
	ON_BN_CLICKED(IDC_RADIO_RECV, &CClientDlg::OnBnClickedRadioRecv)
	//---hj added manually----
	ON_MESSAGE(WM_SOCKET,OnSocket)
	//---hj added manually----
	ON_BN_CLICKED(IDC_BTN_GETP, &CClientDlg::OnBnClickedBtnGetp)
	ON_BN_CLICKED(IDC_BTN_ASK, &CClientDlg::OnBnClickedBtnAsk)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序


BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//init the value of class members
	m_sockClient=INVALID_SOCKET;
	m_bConnect=false;
	//init icon
	//m_hIconClient=AfxGetApp()->LoadIcon(IDI_ICON_CLIENT);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!--use this in ConnServerDlg
	//SetIcon(m_hIconClient,false);
	//init bar
	m_barClient.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP,CRect(0,0,0,0),this,105);
	int arWidth[]={200,-1};
	m_barClient.SetParts(2,arWidth);
	m_barClient.SetText(L"网络状态:  未连接",0,0);
	m_barClient.SetText(L"备注:  ",0,1);

	//set default mode
	CheckRadioButton(IDC_RADIO_SEND,IDC_RADIO_RECV,IDC_RADIO_SEND);
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(false);
	GetDlgItem(IDC_E_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(false);

	//init winsock lib;dont forget ::WSACleanup()
	WSADATA wsaData;
	WORD sockVersion=MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CClientDlg::OnBnClickedRadioSend()
{
	//unenable and invisible the recv-mode stuff
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(false);
	GetDlgItem(IDC_E_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(false);
	//enable and visible my-mode stuff
	GetDlgItem(IDC_E_PUB)->ShowWindow(true);
	GetDlgItem(IDC_BTN_GETP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_GETP)->ShowWindow(true);
	GetDlgItem(IDC_E_OPENFILE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_OPENFILE)->EnableWindow(true);
	GetDlgItem(IDC_BTN_OPENFILE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_ASK)->EnableWindow(true);
	GetDlgItem(IDC_BTN_ASK)->ShowWindow(true);
}


void CClientDlg::OnBnClickedRadioRecv()
{
	//unenable and invisible the send-mode stuff
	GetDlgItem(IDC_E_PUB)->EnableWindow(false);
	GetDlgItem(IDC_E_PUB)->ShowWindow(false);
	GetDlgItem(IDC_BTN_GETP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_GETP)->ShowWindow(false);
	GetDlgItem(IDC_E_OPENFILE)->EnableWindow(false);
	GetDlgItem(IDC_E_OPENFILE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_OPENFILE)->EnableWindow(false);
	GetDlgItem(IDC_BTN_OPENFILE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_ASK)->EnableWindow(false);
	GetDlgItem(IDC_BTN_ASK)->ShowWindow(false);
	//enable and visible my-mode stuff
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(true);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(true);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(true);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(true);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(true);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(true);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(true);
}

//--FD_CONNECT 4 client;FD_ACCEPT 4 server---
bool CClientDlg::CreateAndConn(char* szAddr,unsigned int nPort)
{
	//Notice: in general,CREATE only once,but CONNECT and ShutConn can act many times
	//but here,i BIND them together(Aother Question:?closesocket()关闭,但删除socket了吗)
	if(m_sockClient==INVALID_SOCKET)
	{
		//create
		m_sockClient=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(m_sockClient==INVALID_SOCKET)
			return false;
		//设置为异步消息通知窗口类型
		::WSAAsyncSelect(m_sockClient,m_hWnd,WM_SOCKET,FD_CONNECT|FD_CLOSE|FD_READ|FD_WRITE);
		ULONG uAddr=::inet_addr(szAddr);
		if(uAddr == INADDR_NONE)
			return false;
		//leave out ::bind() can actually work.
		//padding the server addr
		sockaddr_in sinServer;;
		sinServer.sin_addr.S_un.S_addr=uAddr;
		sinServer.sin_family=AF_INET;
		sinServer.sin_port=htons(nPort);
		//connect server
		::connect(m_sockClient,(sockaddr*)&sinServer,sizeof(sockaddr));
		//conn success when receive the FD_CONNECT msg
		return true;
	}
	return false;
}

void CClientDlg::ShutConn()
{
	//no matter how frequently you click the CONNECT btn
	if(m_bConnect)
	{
		if(m_sockClient!=INVALID_SOCKET)
		{
			::closesocket(m_sockClient);
			m_sockClient=INVALID_SOCKET;
			m_bConnect=false;
			//----!!!!!!!!!!!!!!!!!!!!!!!!!!!!相关控件------------
			m_barClient.SetText(L"网络状态:  未连接",0,0);
		}
	}
}

//--the very vital function--
long CClientDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	//get the handle of socket on which event happened
	SOCKET s=wParam;
	//check if error occurs
	int temp=WSAGETSELECTERROR(lParam);
	//if error occurs,WSAGETSELECTERROR return NOT 0--which makes the below sentence true
	if(WSAGETSELECTERROR(lParam)/*==WSAECONNREFUSED*/)
	{
		if(m_sockClient != INVALID_SOCKET)
		{
			//--DO WHAT?----
			::closesocket(m_sockClient);
			m_sockClient=INVALID_SOCKET;
			m_bConnect=false;
		}
		//sth happened lead to unsuccessful connect
		m_barClient.SetText(L"网络状态:  连接出错",0,0);
		return 0;
	}
	//handle the event
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
		{
			//get this msg when conn success,so..
			m_bConnect=true;
			m_barClient.SetText(L"网络状态:  已连接",0,0);
			//---------------TEST,TEST----------------------
			/*peer对方的IP、端口号、主机名
				sockaddr_in sinClient;
				int nSinLen=sizeof(sinClient);
				memset(&sinClient,0,nSinLen);
				::getpeername(s,(sockaddr*)&sinClient,&nSinLen);
				//获取主机字节顺序的端口号
				int nPeerPort=::ntohs(sinClient.sin_port);
				char szPeerPort[10]={0};
				itoa(nPeerPort,szPeerPort,10);//3rd:radix
				//获取主机字节顺序的IP
				char* pchPeerIp=new char[20];
				pchPeerIp=::inet_ntoa(sinClient.sin_addr);
				//--获取对方的主机名--
				//获取网络字节顺序的char ip
				DWORD dwIp=::inet_addr(pchPeerIp);
				HOSTENT* pHost=::gethostbyaddr((LPSTR)&dwIp,4,AF_INET);
				char szHostName[50]={0};
				memcpy(szHostName,pHost->h_name,50);
			//---------------TEST,TEST----------------------*/
		}
		break;
	case FD_READ:
		{
			//recv the net-data directly
			char szText[1024]={0};
			::recv(s,szText,1024,0);
			//judge the msg type
			//if(strcmp(szText))
		}
		break;
	case FD_CLOSE:
		{
			//the peer socket closed when recv this msg,so..
			if(m_sockClient!=INVALID_SOCKET)
			{
				::closesocket(m_sockClient);
				m_sockClient=INVALID_SOCKET;
				m_bConnect=false;
				m_barClient.SetText(L"网络状态:  未连接",0,0);
			}
		}
		break;
		//case FD_WRITE://WRITE is motive/subjective event,just send when needed
	}
	return 0;
}


void CClientDlg::OnBnClickedBtnGetp()
{
	//ask for public key:e
	if(m_bConnect&&m_sockClient!=INVALID_SOCKET)
	{
		::send(m_sockClient,"ask4e\r\n",10,0);
	}
	else if(!m_bConnect)
		MessageBox(L"尚未与签名方建立连接.",L"错误",MB_OK);
}


void CClientDlg::OnBnClickedBtnAsk()
{
	//--TEMP:imitate the real process
	if(m_bConnect && m_sockClient!=INVALID_SOCKET)
	{
		::send(m_sockClient,"ask4sign\r\n",15,0);
	}
	else
		MessageBox(L"尚未与签名方建立连接.",L"错误",MB_OK);
}
