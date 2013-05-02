#pragma once


// CSetBsVarDlg 对话框

class CSetBsVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetBsVarDlg)

public:
	CSetBsVarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetBsVarDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SETBSVAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nSetK;
	afx_msg void OnBnClickedOk();
};
