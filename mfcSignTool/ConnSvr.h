#pragma once


// CConnSvr �Ի���

class CConnSvr : public CDialogEx
{
	DECLARE_DYNAMIC(CConnSvr)

public:
	CConnSvr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConnSvr();

// �Ի�������
	enum { IDD = IDD_DLG_CONNSVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//server ip
	char m_szIpSvr[20];
	//server port
	int m_nPort;
	afx_msg void OnBnClickedOk();
};
