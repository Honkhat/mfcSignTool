// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
//hj added
//self define msg_id (>WM_USER)
#define WM_SOCKET WM_USER+3

// CServerDlg �Ի���

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


// CServerDlg ��Ϣ�������


void CServerDlg::OnBnClickedBtnOpenserv()
{
	//��ǰ��:����û�п���(!Vital!)
	if(!m_bService)
	{
		//Disabled.��֤�����������ڼ䣬ֻ��������һ��;ͬʱ�˵�����ͬ���ܵİ�ťҲDisabled(�����ڸ������Ҫ�������).
		GetDlgItem(IDC_BTN_OPENSERV)->EnableWindow(false);
		m_barServer.SetText(L"����״̬:  ���ڿ�������..",0,0);

		//start service
		//Guarantee this work only once
		if(m_sockServer == INVALID_SOCKET)
		{
			//jude if m_nPort is legal(<1024 is NOT recommended)
			if(m_nPort<1024 || m_nPort>65535)
			{
				MessageBox(L"�˿ںŴ���!( --��Чֵ��Χ:(1024,65535) )",L"����",MB_OK);
				return;
			}
			//create a socket and listen
			if(!CreateAndListen(m_nPort))
			{
				MessageBox(L"�����������!",L"����",MB_OK);
				return;
			}
			//������ش��ڿؼ�
			//extern CmfcSignToolDlg::CStatusBarCtrl m_bar;
			m_barServer.SetText(L"����״̬:  ���ڷ�����..",0,0);
			m_bService=true;
		}
	}
}


BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	m_barServer.SetText(L"����״̬:  ��δ��������",0,0);
	m_barServer.SetText(L"��ע:",0,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CServerDlg::CreateAndListen(int nPort)
{
	//�����ж��׽����Ƿ���Ч(��ֻ֤����һ��:������ֻ�����һ��)
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
	//����m_sockServerΪ�첽��Ϣ֪ͨ��������;ֻ�������ӺͶϿ����󣨶�д��sockClient�У�
	::WSAAsyncSelect(m_sockServer,m_hWnd,WM_SOCKET,FD_ACCEPT|FD_CLOSE);
	//listen
	::listen(m_sockServer,m_nBacklog);

	return true;
}

//����ĵ��첽Socket��Ϣ������ʵ��
long CServerDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	//ȡ�����¼������ľ��
	SOCKET s=wParam;
	//�鿴�Ƿ����
	if(WSAGETSELECTERROR(lParam))
	{
		RemoveClient(s);
		::closesocket(s);
		return 0;
	}
	//���������¼�
	switch(WSAGETSELECTEVENT(lParam))
	{
		//m_sockServerע����FD_ACCEPT;����sockClientû��ע��
	case FD_ACCEPT:
		{
			if(m_nClient<m_nMaxSocket)
			{
				//������������;�������IP
				SOCKET client=::accept(s,NULL,NULL);
				//�����µ�clientΪ�첽��Ϣ֪ͨ�������ͣ�ע��û��ע��FD_ACCEPT
				::WSAAsyncSelect(client,m_hWnd,WM_SOCKET,FD_READ|FD_WRITE|FD_CLOSE);
				//�Ž�client�б���
				AddClient(client);
			}
			else
			{
				MessageBox(L"���ӿͻ�̫��,�������������������!��������������!!",L"����",MB_OK);
			}
		}
		break;
	case FD_CLOSE:
		{
			RemoveClient(s);
			::closesocket(s);
		}
		break;
		//�ɶ�--�������ݰ����͹�����
	case FD_READ:
		{
			//ֱ�ӽ�����������
			char szText[1024]={0};
			::recv(s,szText,1024,0);
			//�ж���Ϣ����: ask4e or ask4sign
			if(strncmp(szText,"ask4e\r\n",6)==0)
			{
				//sendback e
				MessageBox(L"ask4e",L"�յ���Ϣ",MB_OK);
			}
			else if(strcmp(szText,"ask4sign\r\n")==0)
			{
				//peer�Է���IP���˿ںš�������
				sockaddr_in sinClient;
				int nSinLen=sizeof(sinClient);
				memset(&sinClient,0,nSinLen);
				::getpeername(s,(sockaddr*)&sinClient,&nSinLen);
				//��ȡ�����ֽ�˳��Ķ˿ں�
				int nPeerPort=::ntohs(sinClient.sin_port);
				//��ȡ�����ֽ�˳���IP
				char* pchPeerIp=new char[20];
				pchPeerIp=::inet_ntoa(sinClient.sin_addr);
				//--��ȡ�Է���������--
				//��ȡ�����ֽ�˳���char ip
				DWORD dwIp=::inet_addr(pchPeerIp);
				HOSTENT* pHost=::gethostbyaddr((LPSTR)&dwIp,4,AF_INET);
				char szHostName[50]={0};
				memcpy(szHostName,pHost->h_name,50);
				//popup the SignAgreeDlg and send these values to it
				MessageBox(L"ask4sign",L"�յ���Ϣ",MB_OK);
			}
		}
		break;
		//FD_WRITE��������Ϊ,��Ҫ��ʱ��ֱ��::send()���ɡ�
	}
	return 0;
}

bool CServerDlg::AddClient(SOCKET s)
{
	//m_nClient����ָ��δ�����Ԫ��;��Ԫ�ظ���
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
		//���˳�Ա����ĳ�Ա����ǰ�ƶ�һ����λ;jָ��Ҫ������һ��Ԫ���滻��λ��
		for(unsigned int j=i;j<m_nClient-1;j++)
		{
			m_arClient[j]=m_arClient[j+1];
		}
		//����client����
		--m_nClient;
	}
}

void CServerDlg::CloseAllSocket()
{
	//����������ڽ��о͹ر�
	if(m_bService)
	{
		//�رռ����׽���
		if(m_sockServer != INVALID_SOCKET)
		{
			::closesocket(m_sockServer);
			m_sockServer=INVALID_SOCKET;
		}
		//�ر����еĿͻ�����
		for(unsigned int i=0;i<m_nClient;i++)
		{
			::closesocket(m_arClient[i]);
		}
		//����client����
		m_nClient=0;
		//������ؿؼ�״̬
		m_barServer.SetText(L"����״̬:  ֹͣ����",0,0);
		GetDlgItem(IDC_BTN_OPENSERV)->EnableWindow(true);
		m_bService=false;
	}
}