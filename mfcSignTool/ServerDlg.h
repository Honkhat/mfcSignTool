#pragma once
//hj added
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
#define MAX_SOCKET 56

// CServerDlg �Ի���

class CServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	//�����Ƿ��Ѿ�����
	bool m_bService;

	//tag:ֱ�Ӵ������ж��Ƿ��Ѿ�����
	bool CreateAndListen(int nPort);
	//tag:�ر�֮ǰ�ж��Ƿ���Ч
	void CloseAllSocket();
	//tag:���֮ǰ�ж��Ƿ񳬹�m_nMaxSocket
	bool AddClient(SOCKET s);
	//tag:ɾ����ǰ�ж��Ƿ���Ч
	void RemoveClient(SOCKET s);

	//---vital----------
	afx_msg long OnSocket(WPARAM wParam,LPARAM lParama);
	//---vital----------
	afx_msg void OnBnClickedBtnOpenserv();
	virtual BOOL OnInitDialog();
};
