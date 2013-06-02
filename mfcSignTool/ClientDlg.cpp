// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
//hj added
#define WM_SOCKET WM_USER+5
//global variables

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
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CClientDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_UNBLIND, &CClientDlg::OnBnClickedBtnUnblind)
	ON_BN_CLICKED(IDC_BTN_VERIFY, &CClientDlg::OnBnClickedBtnVerify)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序


BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	//but here,i BIND them together(Another Question:?closesocket()关闭,但删除socket了吗)
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
			//judge the msg type by extracting the heading string
			if(strncmp(szText,"backe:",6)==0)
			{
				//去掉报头"backe:",直接改变指针
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
						MessageBox(L"大整数N解析失败!",L"错误",MB_OK);
						return 0;
					}
				}
				else
				{
					MessageBox(L"公钥e解析失败!",L"错误",MB_OK);
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
				SetDlgItemText(IDC_E_RECVSTATE,L"成功接收盲签名!");
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
	//因为用用到公钥e加密盲化消息
	if(m_nE.IsZero()||m_nN.IsZero())
	{
		MessageBox(L"公钥e的值不可为0!",L"错误",MB_OK);
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
			MessageBox(L"尚未与签名方建立连接.",L"错误",MB_OK);
	}
	else
		MessageBox(L"没有选中文档!",L"错误",MB_OK);
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
		MessageBox(L"检测到大整数N为0!",L"错误",MB_OK);
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
		MessageBox(L"给收到的签名去盲失败!",L"错误",MB_OK);
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
		MessageBox(L"检测到公钥E或大整数N为0!",L"错误",MB_OK);
		return;
	}
	Integer fm(m_strMd5Spec.c_str());
	if(fm%m_nN == a_exp_b_mod_c(m_nS,m_nE,m_nN))
	{
		SetDlgItemText(IDC_E_VERIFY,L"身份验证成功,签名是有效的.");
	}
	else
		SetDlgItemText(IDC_E_VERIFY,L"身份验证失败,签名无效.");
}
