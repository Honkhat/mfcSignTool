
// mfcSignToolDlg.h : 头文件
//

#pragma once
//hj added 2 child-style none-border dlgs
#include "ClientDlg.h"
#include "ServerDlg.h"
#include "ConnSvr.h"
#include "RsaVarDlg.h"
#include "PeerInfoDlg.h"
#include "SetRsaVarDlg.h"
#include "SetBsVarDlg.h"
#include "SetSockVarDlg.h"
#include "Md5ToolDlg.h"
#include "AesToolDlg.h"
#include "ClientListDlg.h"
#include "HowDlg.h"
//include winsock related files
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
//save arguments
#include <ShlObj.h>
#include <fstream>

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
	CConnSvr m_dlgConnSvr;
	//当前选择的模式
	bool m_bSignMode;

	//local host name/ip
	char m_szHostName[256];
	char m_szHostIp[20];

	afx_msg void OnBnClickedBtnSideAsk();
	afx_msg void OnBnClickedBtnSideSign();
	afx_msg void OnShutserv();
	afx_msg void OnOpenserv();
	afx_msg void OnMenuShutconn();
	afx_msg void OnConnsvr();
	afx_msg void OnMenuOpenfile();
	afx_msg void OnMenuOutvar();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuAskmode();
	afx_msg void OnMenuSignMode();
	afx_msg void OnMenuDemo();
	afx_msg void OnMenuRsavar();
	afx_msg void OnMenuPeerInfo();
	afx_msg void OnMenuSelfinfo();
	afx_msg void OnMenuBSign();
	afx_msg void OnMenuSockvar();
	afx_msg void OnMenuSetRsaVar();
	afx_msg void OnMenuSetbsvar();
	afx_msg void OnMenuSetsockvar();
	afx_msg void On32793();
	afx_msg void On32794();
	afx_msg void OnMenuClientList();
	afx_msg void OnHowToUse();
};
