#pragma once


// CRsaVarDlg �Ի���

class CRsaVarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRsaVarDlg)

public:
	CRsaVarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRsaVarDlg();

// �Ի�������
	enum { IDD = IDD_DLG_RASVAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	char m_szVarP[430];
	char m_szVarQ[256];
	char m_szVarN[430];
	char m_szVarE[430];
	char m_szVarD[430];
	
public:
	virtual BOOL OnInitDialog();
	//set the class members
	void SetUiText(char* szVarP,char* szVarQ,char* szVarN,char* szVarE,char* szVarD);
};
