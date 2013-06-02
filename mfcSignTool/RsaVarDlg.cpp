// RsaVarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "RsaVarDlg.h"
#include "afxdialogex.h"


// CRsaVarDlg �Ի���

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


// CRsaVarDlg ��Ϣ�������

//call this function in OnInitDialog
void CRsaVarDlg::SetUiText(char* szVarP,char* szVarQ,char* szVarN,char* szVarE,char* szVarD)
{
	memcpy(m_szVarP,szVarP,MAX_HEX_DIGITS);
	memcpy(m_szVarQ,szVarQ,MAX_HEX_DIGITS);
	memcpy(m_szVarN,szVarN,MAX_HEX_DIGITS);
	memcpy(m_szVarE,szVarE,MAX_HEX_DIGITS);
	memcpy(m_szVarD,szVarD,MAX_HEX_DIGITS);
}

BOOL CRsaVarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	wchar_t wszTmp[MAX_HEX_DIGITS]={0};
	MultiByteToWideChar(CP_ACP,0,m_szVarP,-1,wszTmp,MAX_HEX_DIGITS);
	SetDlgItemText(IDC_E_VARP,wszTmp);
	memset(wszTmp,0,MAX_HEX_DIGITS);
	MultiByteToWideChar(CP_ACP,0,m_szVarQ,-1,wszTmp,MAX_HEX_DIGITS);
	SetDlgItemText(IDC_E_VARQ,wszTmp);
	memset(wszTmp,0,MAX_HEX_DIGITS);
	MultiByteToWideChar(CP_ACP,0,m_szVarN,-1,wszTmp,MAX_HEX_DIGITS);
	SetDlgItemText(IDC_E_VARN,wszTmp);
	memset(wszTmp,0,MAX_HEX_DIGITS);
	MultiByteToWideChar(CP_ACP,0,m_szVarE,-1,wszTmp,MAX_HEX_DIGITS);
	SetDlgItemText(IDC_E_VARE,wszTmp);
	memset(wszTmp,0,MAX_HEX_DIGITS);
	MultiByteToWideChar(CP_ACP,0,m_szVarD,-1,wszTmp,MAX_HEX_DIGITS);
	SetDlgItemText(IDC_E_VARD,wszTmp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
