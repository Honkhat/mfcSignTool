#pragma once
//hj added
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
#define MAX_SOCKET 56

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

	//tag:直接创建不判断是否已经创建
	bool CreateAndListen(int nPort);
	//tag:关闭之前判断是否有效
	void CloseAllSocket();
	//tag:添加之前判断是否超过m_nMaxSocket
	bool AddClient(SOCKET s);
	//tag:删除以前判断是否有效
	void RemoveClient(SOCKET s);

	//---vital----------
	afx_msg long OnSocket(WPARAM wParam,LPARAM lParama);
	//---vital----------
	afx_msg void OnBnClickedBtnOpenserv();
	virtual BOOL OnInitDialog();
};
