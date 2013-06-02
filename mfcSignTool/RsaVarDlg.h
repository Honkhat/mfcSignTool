#pragma once

#define MAX_HEX_DIGITS 520
// CRsaVarDlg 对话框

class CRsaVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRsaVarDlg)

public:
	CRsaVarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRsaVarDlg();

// 对话框数据
	enum { IDD = IDD_DLG_RASVAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	char m_szVarP[MAX_HEX_DIGITS];
	char m_szVarQ[MAX_HEX_DIGITS];
	char m_szVarN[MAX_HEX_DIGITS];
	char m_szVarE[MAX_HEX_DIGITS];
	char m_szVarD[MAX_HEX_DIGITS];
	
public:
	virtual BOOL OnInitDialog();
	//set the class members
	void SetUiText(char* szVarP,char* szVarQ,char* szVarN,char* szVarE,char* szVarD);
};
