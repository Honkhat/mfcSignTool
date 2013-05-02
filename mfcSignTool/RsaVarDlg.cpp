// RsaVarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "RsaVarDlg.h"
#include "afxdialogex.h"


// CRsaVarDlg 对话框

IMPLEMENT_DYNAMIC(CRsaVarDlg, CDialogEx)

CRsaVarDlg::CRsaVarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRsaVarDlg::IDD, pParent)
{

}

CRsaVarDlg::~CRsaVarDlg()
{
}

void CRsaVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRsaVarDlg, CDialogEx)
END_MESSAGE_MAP()


// CRsaVarDlg 消息处理程序

//call this function in OnInitDialog
void CRsaVarDlg::SetUiText(char* szVarP,char* szVarQ,char* szVarN,char* szVarE,char* szVarD)
{
	memcpy(m_szVarP,szVarP,430);
	memcpy(m_szVarQ,szVarQ,430);
	memcpy(m_szVarN,szVarN,430);
	memcpy(m_szVarE,szVarE,430);
	memcpy(m_szVarD,szVarD,430);
}

BOOL CRsaVarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	wchar_t wszTmp[430]={0};
	MultiByteToWideChar(CP_ACP,0,m_szVarP,-1,wszTmp,430);
	SetDlgItemText(IDC_E_VARP,wszTmp);
	memset(wszTmp,0,430);
	MultiByteToWideChar(CP_ACP,0,m_szVarQ,-1,wszTmp,430);
	SetDlgItemText(IDC_E_VARQ,wszTmp);
	memset(wszTmp,0,430);
	MultiByteToWideChar(CP_ACP,0,m_szVarN,-1,wszTmp,430);
	SetDlgItemText(IDC_E_VARN,wszTmp);
	memset(wszTmp,0,430);
	MultiByteToWideChar(CP_ACP,0,m_szVarE,-1,wszTmp,430);
	SetDlgItemText(IDC_E_VARE,wszTmp);
	memset(wszTmp,0,430);
	MultiByteToWideChar(CP_ACP,0,m_szVarD,-1,wszTmp,430);
	SetDlgItemText(IDC_E_VARD,wszTmp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
