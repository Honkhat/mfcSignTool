// SignYonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "SignYonDlg.h"
#include "afxdialogex.h"


// CSignYonDlg 对话框

IMPLEMENT_DYNAMIC(CSignYonDlg, CDialogEx)

CSignYonDlg::CSignYonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSignYonDlg::IDD, pParent)
{

}

CSignYonDlg::~CSignYonDlg()
{
}

void CSignYonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSignYonDlg, CDialogEx)
END_MESSAGE_MAP()


// CSignYonDlg 消息处理程序
void CSignYonDlg::SetUiText(char* szFromIp,char* szFromPort,char* szPeerName,char* szText)
{
	memcpy(m_szFromIp,szFromIp,20);
	memcpy(m_szFromPort,szFromPort,10);
	memcpy(m_szPeerName,szPeerName,50);
	memcpy(m_szText,szText,1024);
}

BOOL CSignYonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//char-->wchat_t-->CString NEED?
	CString csTmp;
	csTmp=m_szFromIp;
	SetDlgItemText(IDC_E_FROMIP,csTmp);
	csTmp.Empty();
	csTmp=m_szFromPort;
	SetDlgItemText(IDC_E_FROMPORT,csTmp);

	csTmp.Empty();
	csTmp=m_szPeerName;
	SetDlgItemText(IDC_E_PEERNAME,csTmp);

	csTmp.Empty();
	csTmp=m_szText;
	SetDlgItemText(IDC_E_MDRECV,csTmp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
