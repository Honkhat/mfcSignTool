#pragma once
//for validating the set values
#include <integer.h>
using CryptoPP::Integer;
using CryptoPP::a_exp_b_mod_c;
// CSetRsaVarDlg �Ի���

class CSetRsaVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRsaVarDlg)

public:
	CSetRsaVarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetRsaVarDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SETRSA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
