#pragma once


// CSetSockVarDlg �Ի���

class CSetSockVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSockVarDlg)

public:
	CSetSockVarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetSockVarDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SETSOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nSetMaxClient;
	int m_nSetBacklog;
	int m_nSetPort;
	afx_msg void OnBnClickedOk();
};
