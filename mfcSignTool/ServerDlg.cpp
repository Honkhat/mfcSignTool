// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
//hj added
//self define msg_id (>WM_USER)
#define WM_SOCKET WM_USER+3

// CServerDlg 对话框

IMPLEMENT_DYNAMIC(CServerDlg, CDialogEx)

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{

}

CServerDlg::~CServerDlg()
{
	CloseAllSocket();
	::WSACleanup();
	
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPENSERV, &CServerDlg::OnBnClickedBtnOpenserv)
	//--hj added manually--
	ON_MESSAGE(WM_SOCKET,OnSocket)
	//--hj added manually--
END_MESSAGE_MAP()


// CServerDlg 消息处理程序


void CServerDlg::OnBnClickedBtnOpenserv()
{
	//大前提:服务没有开启(!Vital!)
	if(!m_bService)
	{
		//Disabled.保证在整个软件活动期间，只开启服务一次;同时菜单中相同功能的按钮也Disabled(由于在父层次需要点击触发).
		GetDlgItem(IDC_BTN_OPENSERV)->EnableWindow(false);
		m_barServer.SetText(L"网络状态:  正在开启服务..",0,0);

		//start service
		//Guarantee this work only once
		if(m_sockServer == INVALID_SOCKET)
		{
			//jude if m_nPort is legal(<1024 is NOT recommended)
			if(m_nPort<1024 || m_nPort>65535)
			{
				MessageBox(L"端口号错误!( --有效值范围:(1024,65535) )",L"错误",MB_OK);
				return;
			}
			//create a socket and listen
			if(!CreateAndListen(m_nPort))
			{
				MessageBox(L"开启服务出错!",L"错误",MB_OK);
				return;
			}
			//设置相关窗口控件
			//extern CmfcSignToolDlg::CStatusBarCtrl m_bar;
			m_barServer.SetText(L"网络状态:  正在服务中..",0,0);
			m_bService=true;
		}
	}
}


BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//Initialize the value of class members
	m_nMaxSocket=56;
	m_nBacklog=5;
	m_sockServer=INVALID_SOCKET;
	m_nPort=12345;
	m_nClient=0;
	m_bService=false;

	//Initialize the winsock lib
	WSADATA wsaData;
	WORD sockVersion=MAKEWORD(2,0);
	::WSAStartup(sockVersion,&wsaData);

	//Initialize bar
	m_barServer.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP,CRect(0,0,0,0),this,102);
	//m_barServer.SetBkColor(RGB(0xa6,0xca,0xf0));//Didn't work.
	int arWidth[]={220,-1};
	m_barServer.SetParts(2,arWidth);
	m_barServer.SetText(L"网络状态:  尚未开启服务",0,0);
	m_barServer.SetText(L"备注:",0,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool CServerDlg::CreateAndListen(int nPort)
{
	//首先判断套接字是否有效(保证只创建一次:界面上只允许点一次)
	if(m_sockServer != INVALID_SOCKET)
	{
		::closesocket(m_sockServer);
	}
	//create new
	m_sockServer=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(m_sockServer==INVALID_SOCKET)
		return false;
	//----abt to bind----
	//--get local ip--
	char szHost[256]={0};
	::gethostname(szHost,256);
	hostent* pHost=gethostbyname(szHost);
	ULONG ulLocalIp=0;
	if(pHost!=NULL)
	{
		in_addr* pMyaddr=(in_addr*)*(pHost->h_addr_list);
		char szIp[20]={0};
		memcpy(szIp,inet_ntoa(pMyaddr[0]),20);
		ulLocalIp=inet_addr(szIp);

	}
	else
	{
		ulLocalIp=inet_addr("127.0.0.1");
	}
	//--get local ip over--
	sockaddr_in sinServer;
	sinServer.sin_family=AF_INET;
	sinServer.sin_port=htons(m_nPort);
	sinServer.sin_addr.S_un.S_addr=ulLocalIp;
	
	if(::bind(m_sockServer,(sockaddr*)&sinServer,sizeof(sinServer))==SOCKET_ERROR)
	{
		return false;
	}
	//----bind over----
	//设置m_sockServer为异步消息通知窗口类型;只处理连接和断开请求（读写在sockClient中）
	::WSAAsyncSelect(m_sockServer,m_hWnd,WM_SOCKET,FD_ACCEPT|FD_CLOSE);
	//listen
	::listen(m_sockServer,m_nBacklog);

	return true;
}

//最核心的异步Socket消息处理函数实现
long CServerDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	//取得有事件发生的句柄
	SOCKET s=wParam;
	//查看是否出错
	if(WSAGETSELECTERROR(lParam))
	{
		RemoveClient(s);
		::closesocket(s);
		return 0;
	}
	//处理发生的事件
	switch(WSAGETSELECTEVENT(lParam))
	{
		//m_sockServer注册了FD_ACCEPT;其他sockClient没有注册
	case FD_ACCEPT:
		{
			if(m_nClient<m_nMaxSocket)
			{
				//接受连接请求;不判身份IP
				SOCKET client=::accept(s,NULL,NULL);
				//设置新的client为异步消息通知窗口类型，注意没有注册FD_ACCEPT
				::WSAAsyncSelect(client,m_hWnd,WM_SOCKET,FD_READ|FD_WRITE|FD_CLOSE);
				//放进client列表里
				AddClient(client);
			}
			else
			{
				MessageBox(L"连接客户太多,超过了最大连接数限制!将忽略连接请求!!",L"警告",MB_OK);
			}
		}
		break;
	case FD_CLOSE:
		{
			RemoveClient(s);
			::closesocket(s);
		}
		break;
		//可读--即有数据包发送过来了
	case FD_READ:
		{
			//直接接收网络数据
			char szText[1024]={0};
			::recv(s,szText,1024,0);
			//判断消息类型: ask4e or ask4sign
			if(strncmp(szText,"ask4e\r\n",6)==0)
			{
				//sendback e
				MessageBox(L"ask4e",L"收到消息",MB_OK);
			}
			else if(strcmp(szText,"ask4sign\r\n")==0)
			{
				//peer对方的IP、端口号、主机名
				sockaddr_in sinClient;
				int nSinLen=sizeof(sinClient);
				memset(&sinClient,0,nSinLen);
				::getpeername(s,(sockaddr*)&sinClient,&nSinLen);
				//获取主机字节顺序的端口号
				int nPeerPort=::ntohs(sinClient.sin_port);
				//获取主机字节顺序的IP
				char* pchPeerIp=new char[20];
				pchPeerIp=::inet_ntoa(sinClient.sin_addr);
				//--获取对方的主机名--
				//获取网络字节顺序的char ip
				DWORD dwIp=::inet_addr(pchPeerIp);
				HOSTENT* pHost=::gethostbyaddr((LPSTR)&dwIp,4,AF_INET);
				char szHostName[50]={0};
				memcpy(szHostName,pHost->h_name,50);
				//popup the SignAgreeDlg and send these values to it
				MessageBox(L"ask4sign",L"收到消息",MB_OK);
			}
		}
		break;
		//FD_WRITE是主动行为,需要的时候直接::send()即可。
	}
	return 0;
}

bool CServerDlg::AddClient(SOCKET s)
{
	//m_nClient总是指向未分配的元素;即元素个数
	if(m_nClient<m_nMaxSocket)
	{
		m_arClient[m_nClient++]=s;
		return true;
	}
	return false;
}

void CServerDlg::RemoveClient(SOCKET s)
{
	bool bFind=false;
	unsigned int i=0;
	for(;i<m_nClient;i++)
	{
		if(m_arClient[i] == s)
		{
			bFind=true;
			break;
		}
	}
	if(bFind)
	{
		//将此成员后面的成员都向前移动一个单位;j指向要被后面一个元素替换的位置
		for(unsigned int j=i;j<m_nClient-1;j++)
		{
			m_arClient[j]=m_arClient[j+1];
		}
		//更新client总数
		--m_nClient;
	}
}

void CServerDlg::CloseAllSocket()
{
	//如果服务正在进行就关闭
	if(m_bService)
	{
		//关闭监听套接字
		if(m_sockServer != INVALID_SOCKET)
		{
			::closesocket(m_sockServer);
			m_sockServer=INVALID_SOCKET;
		}
		//关闭所有的客户连接
		for(unsigned int i=0;i<m_nClient;i++)
		{
			::closesocket(m_arClient[i]);
		}
		//更新client总数
		m_nClient=0;
		//更新相关控件状态
		m_barServer.SetText(L"网络状态:  停止服务",0,0);
		GetDlgItem(IDC_BTN_OPENSERV)->EnableWindow(true);
		m_bService=false;
	}
}