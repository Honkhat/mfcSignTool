// SetBsVarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "SetBsVarDlg.h"
#include "afxdialogex.h"


// CSetBsVarDlg 对话框

IMPLEMENT_DYNAMIC(CSetBsVarDlg, CDialogEx)

CSetBsVarDlg::CSetBsVarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetBsVarDlg::IDD, pParent)
{

}

CSetBsVarDlg::~CSetBsVarDlg()
{
}

void CSetBsVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetBsVarDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetBsVarDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetBsVarDlg 消息处理程序


void CSetBsVarDlg::OnBnClickedOk()
{
	//get n(int)
	wchar_t wszTmp[10]={0};
	char szTmp[10]={0};
	GetDlgItemText(IDC_E_SETK,wszTmp,10);
	WideCharToMultiByte(CP_ACP,0,wszTmp,-1,szTmp,10,NULL,NULL);
	m_nSetK=atoi(szTmp);
	if(m_nSetK<100)
	{
		MessageBox(L"K值太小,至少大于100吧.",L"Warning",MB_OK);
		return;
	}
	CDialogEx::OnOK();
}
