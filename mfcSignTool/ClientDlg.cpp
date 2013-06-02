// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
//hj added
#define WM_SOCKET WM_USER+5
//global variables

// CClientDlg �Ի���

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
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CClientDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_UNBLIND, &CClientDlg::OnBnClickedBtnUnblind)
	ON_BN_CLICKED(IDC_BTN_VERIFY, &CClientDlg::OnBnClickedBtnVerify)
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������


BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//init the value of class members
	m_sockClient=INVALID_SOCKET;
	m_bConnect=false;
	memset(m_szFileSpec,0,MAX_PATH);
	//----RSA related  begin-----
	m_nK=Integer(128);
	//----RSA related  end-------
	//init icon
	//m_hIconClient=AfxGetApp()->LoadIcon(IDI_ICON_CLIENT);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!--use this in ConnServerDlg
	//SetIcon(m_hIconClient,false);
	//init bar
	m_barClient.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP,CRect(0,0,0,0),this,105);
	int arWidth[]={200,-1};
	m_barClient.SetParts(2,arWidth);
	m_barClient.SetText(L"����״̬:  δ����",0,0);
	m_barClient.SetText(L"��ע:  ",0,1);

	//set default mode
	CheckRadioButton(IDC_RADIO_SEND,IDC_RADIO_RECV,IDC_RADIO_SEND);
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(false);
	//GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);//coz:ReadOnly property
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
	// �쳣: OCX ����ҳӦ���� FALSE
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
	//GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);//coz: ReadOnly property
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
	//GetDlgItem(IDC_E_PUB)->EnableWindow(false);
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
	//but here,i BIND them together(Another Question:?closesocket()�ر�,��ɾ��socket����)
	if(m_sockClient==INVALID_SOCKET)
	{
		//create
		m_sockClient=::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(m_sockClient==INVALID_SOCKET)
			return false;
		//����Ϊ�첽��Ϣ֪ͨ��������
		::WSAAsyncSelect(m_sockClient,m_hWnd,WM_SOCKET,FD_CONNECT|FD_CLOSE|FD_READ|FD_WRITE);
		ULONG uAddr=::inet_addr(szAddr);
		if(uAddr == INADDR_NONE)
			return false;
		//leave out ::bind() can actually work.
		//padding the server addr
		sockaddr_in sinServer;
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
			if(m_barClient)
				m_barClient.SetText(L"����״̬:  δ����",0,0);
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
		m_barClient.SetText(L"����״̬:  ���ӳ���",0,0);
		return 0;
	}
	//handle the event
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
		{
			//get this msg when conn success,so..
			m_bConnect=true;
			m_barClient.SetText(L"����״̬:  ������",0,0);
			//---------------TEST,TEST----------------------
			/*peer�Է���IP���˿ںš�������
				sockaddr_in sinClient;
				int nSinLen=sizeof(sinClient);
				memset(&sinClient,0,nSinLen);
				::getpeername(s,(sockaddr*)&sinClient,&nSinLen);
				//��ȡ�����ֽ�˳��Ķ˿ں�
				int nPeerPort=::ntohs(sinClient.sin_port);
				char szPeerPort[10]={0};
				itoa(nPeerPort,szPeerPort,10);//3rd:radix
				//��ȡ�����ֽ�˳���IP
				char* pchPeerIp=new char[20];
				pchPeerIp=::inet_ntoa(sinClient.sin_addr);
				//--��ȡ�Է���������--
				//��ȡ�����ֽ�˳���char ip
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
			//judge the msg type by extracting the heading string
			if(strncmp(szText,"backe:",6)==0)
			{
				//ȥ����ͷ"backe:",ֱ�Ӹı�ָ��
				char* pszText=szText;
				pszText=&szText[6];
				wchar_t wszText[1024]={0};
				MultiByteToWideChar(CP_ACP,0,pszText,-1,wszText,1024);
				SetDlgItemText(IDC_E_PUB,wszText);
				//extract m_nE,m_nN
				char* pTmp=NULL;
				if(pTmp=strtok(pszText,"\r\n"))
				{
					//set m_nE
					m_nE=Integer(pTmp);
					if(pTmp=strtok(NULL,""))
					{
						//set m_nN
						m_nN=Integer(pTmp);
					}
					else
					{
						MessageBox(L"������N����ʧ��!",L"����",MB_OK);
						return 0;
					}
				}
				else
				{
					MessageBox(L"��Կe����ʧ��!",L"����",MB_OK);
					return 0;
				}
			}
			//Other type msg processing..
			else if(strncmp(szText,"backsign:",9)==0)
			{
				//wipe out "backsign:" and set m_nSs
				char* pszText=szText;
				pszText=&szText[9];
				m_nSs=Integer(pszText);
				//disp on UI
				SetDlgItemText(IDC_E_RECVSTATE,L"�ɹ�����äǩ��!");
			}
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
				if(m_barClient)
					m_barClient.SetText(L"����״̬:  δ����",0,0);
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
		MessageBox(L"��δ��ǩ������������.",L"����",MB_OK);
}


void CClientDlg::OnBnClickedBtnAsk()
{
	//��Ϊ���õ���Կe����ä����Ϣ
	if(m_nE.IsZero()||m_nN.IsZero())
	{
		MessageBox(L"��Կe��ֵ����Ϊ0!",L"����",MB_OK);
		return;
	}
	//First check if set m_szFileSpec
	if(strcmp(m_szFileSpec,"")!=0)
	{
		CalcMd5ForFile(m_szFileSpec,m_strMd5Spec);

		if(m_bConnect && m_sockClient!=INVALID_SOCKET)
		{
			//blind the MessageDigest
			Integer fm(m_strMd5Spec.c_str());
			Integer mb=a_exp_b_mod_c(m_nK,m_nE,m_nN);
			mb=mb*fm%m_nN;
			//mb-->char
			stringstream sstream;
			char szTmp[520]={0};
			sstream<<hex<<mb;
			sstream>>szTmp;
			//padding szText;Format: ask4sign(+m_strMd5Spec)
			char szText[1024]={0};
			strncat(szText,"ask4sign",10);
			strncat(szText,szTmp,520);
			::send(m_sockClient,szText,1024,0);
		}
		else
			MessageBox(L"��δ��ǩ������������.",L"����",MB_OK);
	}
	else
		MessageBox(L"û��ѡ���ĵ�!",L"����",MB_OK);
}

void CClientDlg::CalcMd5ForFile(char* szFileName,string& strMd5)
{
	MD5 hash;
	byte buffer[2*MD5::DIGESTSIZE];
	FileSource(szFileName,true,new HashFilter(hash,new HexEncoder(new ArraySink(buffer,2*MD5::DIGESTSIZE))));
	string str_md5((const char*)buffer,2*MD5::DIGESTSIZE);
	strMd5=str_md5;
}

void CClientDlg::OnBnClickedBtnOpenfile()
{
	//open the file to be signed
	wchar_t szOpenFile[MAX_PATH]={0};

	OPENFILENAME OpenFile={0};
	OpenFile.lStructSize=sizeof(OpenFile);
	OpenFile.lpstrFile=szOpenFile;
	OpenFile.nMaxFile=MAX_PATH;
	OpenFile.lpstrFilter=L"Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	OpenFile.nFilterIndex=1;
	if(::GetOpenFileName(&OpenFile))
	{
		//UpdateData(false)
		SetDlgItemText(IDC_E_OPENFILE,szOpenFile);
		//set the m_szFileSpec
		WideCharToMultiByte(CP_ACP,0,szOpenFile,-1,m_szFileSpec,MAX_PATH,NULL,NULL);
	}
}


void CClientDlg::OnBnClickedBtnUnblind()
{
	if(m_nN.IsZero())
	{
		MessageBox(L"��⵽������NΪ0!",L"����",MB_OK);
		return;
	}
	//s=s'/k (+..n)
	int i=0;
	for(;i<1000000;i++)
	{
		if(m_nSs%m_nK==0)
			break;
		m_nSs+=m_nN;
	}
	if(i==1000000)
	{
		MessageBox(L"���յ���ǩ��ȥäʧ��!",L"����",MB_OK);
		return;
	}
	m_nS=m_nSs/m_nK;
	//disp on UI
	stringstream sstream;
	char szTmp[520]={0};
	wchar_t wszTmp[520]={0};
	sstream<<hex<<m_nS;
	sstream>>szTmp;
	MultiByteToWideChar(CP_ACP,0,szTmp,-1,wszTmp,520);
	SetDlgItemText(IDC_E_UNBLIND,wszTmp);
}


void CClientDlg::OnBnClickedBtnVerify()
{
	if(m_nE.IsZero()||m_nN.IsZero())
	{
		MessageBox(L"��⵽��ԿE�������NΪ0!",L"����",MB_OK);
		return;
	}
	Integer fm(m_strMd5Spec.c_str());
	if(fm%m_nN == a_exp_b_mod_c(m_nS,m_nE,m_nN))
	{
		SetDlgItemText(IDC_E_VERIFY,L"�����֤�ɹ�,ǩ������Ч��.");
	}
	else
		SetDlgItemText(IDC_E_VERIFY,L"�����֤ʧ��,ǩ����Ч.");
}
