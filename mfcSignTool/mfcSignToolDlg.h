
// mfcSignToolDlg.h : ͷ�ļ�
//

#pragma once
//hj added 2 child-style none-border dlgs
#include "ClientDlg.h"
#include "ServerDlg.h"

// CmfcSignToolDlg �Ի���
class CmfcSignToolDlg : public CDialogEx
{
// ����
public:
	CmfcSignToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCSIGNTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	afx_msg void OnBnClickedBtnSideAsk();
	afx_msg void OnBnClickedBtnSideSign();
};
