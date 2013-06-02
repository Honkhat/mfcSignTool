#pragma once
//hj added
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
#define MAX_SOCKET 56

#include "SignYonDlg.h"
//stringstream<<hex<<Integer
#include <sstream>
using namespace std;
//16 radix(about 512 decimal radix)
#define MAX_INT_DIGITS 520
//---RSA related begin-----
#include <osrng.h>
#include <integer.h>
#include <rsa.h>
using namespace CryptoPP;
//---RSA related end  -----
// CServerDlg 对话框

class CServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSignYonDlg m_dlgSignYon;
	//the maximum num of clients allowed(m_nMaxSocket<MAX_SOCKET !)
	unsigned int m_nMaxSocket;
	//the backlog
	int m_nBacklog;
	//the port both client and server agreed
	unsigned int m_nPort;
	//the main socket of server
	SOCKET m_sockServer;
	//the client sock array
	SOCKET m_arClient[MAX_SOCKET];
	//the length of m_arClient(always point to the space-allocated-not element suffix)
	unsigned int m_nClient;
	//StatusBar
	CStatusBarCtrl m_barServer;
	//服务是否已经开启
	bool m_bService;
	//---RSA related begin----
	RSA::PrivateKey m_privKey;
	Integer m_rsaE;//public key
	char    m_szE[MAX_INT_DIGITS];
	Integer m_rsaD;//private key
	Integer m_rsaN;//N=P*Q
	char    m_szN[MAX_INT_DIGITS];
	Integer m_rsaP;//Big Prim 1
	Integer m_rsaQ;//Big Prim 2
	unsigned int m_nKeySize;//key size
	//---RSA related end  ----

	//tag:直接创建不判断是否已经创建
	bool CreateAndListen(int nPort);
	//tag:关闭之前判断是否有效
	void CloseAllSocket();
	//tag:添加之前判断是否超过m_nMaxSocket
	bool AddClient(SOCKET s);
	//tag:删除之前判断是否有效
	void RemoveClient(SOCKET s);

	//---vital----------
	afx_msg long OnSocket(WPARAM wParam,LPARAM lParama);
	//---vital----------
	afx_msg void OnBnClickedBtnOpenserv();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRandgen();
};
