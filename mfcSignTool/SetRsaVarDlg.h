#pragma once
//for validating the set values
#include <integer.h>
using CryptoPP::Integer;
using CryptoPP::a_exp_b_mod_c;
// CSetRsaVarDlg 对话框

class CSetRsaVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRsaVarDlg)

public:
	CSetRsaVarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetRsaVarDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SETRSA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_setn;
	CString m_sete;
	CString m_setd;
	Integer m_intSetN;
	Integer m_intSetE;
	Integer m_intSetD;
};
