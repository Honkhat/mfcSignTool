#pragma once

#define MAX_HEX_DIGITS 520
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
