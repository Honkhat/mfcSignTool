#pragma once


// CSetBsVarDlg �Ի���

class CSetBsVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetBsVarDlg)

public:
	CSetBsVarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetBsVarDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SETBSVAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nSetK;
	afx_msg void OnBnClickedOk();
};
