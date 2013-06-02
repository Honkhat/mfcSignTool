// SetRsaVarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "SetRsaVarDlg.h"
#include "afxdialogex.h"


// CSetRsaVarDlg 对话框

IMPLEMENT_DYNAMIC(CSetRsaVarDlg, CDialogEx)

CSetRsaVarDlg::CSetRsaVarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetRsaVarDlg::IDD, pParent)
	, m_setn(_T(""))
	, m_sete(_T(""))
	, m_setd(_T(""))
{

}

CSetRsaVarDlg::~CSetRsaVarDlg()
{
}

void CSetRsaVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_SETN, m_setn);
	DDX_Text(pDX, IDC_E_SETE, m_sete);
	DDX_Text(pDX, IDC_E_SETD, m_setd);
}


BEGIN_MESSAGE_MAP(CSetRsaVarDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetRsaVarDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetRsaVarDlg 消息处理程序


void CSetRsaVarDlg::OnBnClickedOk()
{
	//SignToolDlg must be in the SignMode
	//UpdateData(true) before close
	UpdateData(true);
	//validate
	char szTmp[MAX_HEX_DIGITS]={0};
	WideCharToMultiByte(CP_ACP,0,m_setn.GetString(),-1,szTmp,MAX_HEX_DIGITS,NULL,NULL);
	m_intSetN=Integer(szTmp);

	memset(szTmp,0,MAX_HEX_DIGITS);
	WideCharToMultiByte(CP_ACP,0,m_sete.GetString(),-1,szTmp,MAX_HEX_DIGITS,NULL,NULL);
	m_intSetE=Integer(szTmp);

	memset(szTmp,0,MAX_HEX_DIGITS);
	WideCharToMultiByte(CP_ACP,0,m_setd.GetString(),-1,szTmp,MAX_HEX_DIGITS,NULL,NULL);
    m_intSetD=Integer(szTmp);

	Integer nTest(100);
	if(nTest != a_exp_b_mod_c(a_exp_b_mod_c(nTest,m_intSetE,m_intSetN),m_intSetD,m_intSetN))
	{
		MessageBox(L"设置的RSA参数无效!",L"ERROR",MB_OK);
		return;
	}
	
	CDialogEx::OnOK();
}
