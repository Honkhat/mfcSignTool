#pragma once


// CSetSockVarDlg 对话框

class CSetSockVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSockVarDlg)

public:
	CSetSockVarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetSockVarDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SETSOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nSetMaxClient;
	int m_nSetBacklog;
	int m_nSetPort;
	afx_msg void OnBnClickedOk();
};
