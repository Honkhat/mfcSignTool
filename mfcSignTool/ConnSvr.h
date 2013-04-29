#pragma once


// CConnSvr 对话框

class CConnSvr : public CDialogEx
{
	DECLARE_DYNAMIC(CConnSvr)

public:
	CConnSvr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConnSvr();

// 对话框数据
	enum { IDD = IDD_DLG_CONNSVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//server ip
	char m_szIpSvr[20];
	//server port
	int m_nPort;
	afx_msg void OnBnClickedOk();
};
