#pragma once


// CPeerInfoDlg 对话框

class CPeerInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPeerInfoDlg)

public:
	CPeerInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeerInfoDlg();

// 对话框数据
	enum { IDD = IDD_DLG_PEERINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	char m_szPeerIp[20];
	char m_szPeerPort[10];
	char m_szPeerName[50];
	//set the UI control values
	void setUiText(char* szPeerIp,char* szPeerPort,char* szPeerName);
	virtual BOOL OnInitDialog();
};
