#pragma once


// CSignYonDlg 对话框

class CSignYonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignYonDlg)

public:
	CSignYonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSignYonDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SIGN_YON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//from IP
	char m_szFromIp[20];
	//from port
	char m_szFromPort[10];
	//from hostname
	char m_szPeerName[50];
	//the MessageDigest received
	char m_szText[1024];
	//set all the text on the surface
	void SetUiText(char* szFromIp,char* szFromPort,char* szPeerName,char* szText);
	virtual BOOL OnInitDialog();
};
