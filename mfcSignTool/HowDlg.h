#pragma once


// CHowDlg 对话框

class CHowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHowDlg)

public:
	CHowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHowDlg();

// 对话框数据
	enum { IDD = IDD_DLG_HOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
