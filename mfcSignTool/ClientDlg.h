#pragma once
//hj added
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")

// CClientDlg �Ի���

class CClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientDlg)

public:
	CClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClientDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatusBarCtrl m_barClient;
	SOCKET m_sockClient;
	//status:whether connect server or not
	bool m_bConnect;

	virtual BOOL OnInitDialog();
	//Function: create a socket and connect server
	bool CreateAndConn(char* szAddr,unsigned int nPort);
	//shut connect down
	void ShutConn();

	afx_msg void OnBnClickedRadioSend();
	afx_msg void OnBnClickedRadioRecv();
	//--vital---
	afx_msg long OnSocket(WPARAM wParam,LPARAM lParam);
	//--vital---
	afx_msg void OnBnClickedBtnGetp();
	afx_msg void OnBnClickedBtnAsk();
};
