
// mfcSignToolDlg.h : 头文件
//

#pragma once
//hj added 2 child-style none-border dlgs
#include "ClientDlg.h"
#include "ServerDlg.h"
//include winsock related files
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")


// CmfcSignToolDlg 对话框
class CmfcSignToolDlg : public CDialogEx
{
// 构造
public:
	CmfcSignToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCSIGNTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatusBarCtrl m_bar;
	HICON m_hIconOn;
	HICON m_hIconOff;
	CButton m_btnSideAsk;
	CButton m_btnSideSign;
	CClientDlg m_dlgClient;
	CServerDlg m_dlgServer;
	//当前选择的模式
	bool m_bSignMode;

	//local host name/ip
	char m_szHostName[256];
	char m_szHostIp[20];

	afx_msg void OnBnClickedBtnSideAsk();
	afx_msg void OnBnClickedBtnSideSign();
	afx_msg void OnShutserv();
	afx_msg void OnOpenserv();
};
