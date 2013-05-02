// SetSockVarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "SetSockVarDlg.h"
#include "afxdialogex.h"


// CSetSockVarDlg �Ի���

IMPLEMENT_DYNAMIC(CSetSockVarDlg, CDialogEx)

CSetSockVarDlg::CSetSockVarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSockVarDlg::IDD, pParent)
{

}

CSetSockVarDlg::~CSetSockVarDlg()
{
}

void CSetSockVarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetSockVarDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetSockVarDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetSockVarDlg ��Ϣ�������


void CSetSockVarDlg::OnBnClickedOk()
{
	//get the value (int)
	UpdateData(true);
	wchar_t wszTmp[10]={0};
	char    szTmp[10]={0};
	GetDlgItemText(IDC_E_SETBACKLOG,wszTmp,10);
	WideCharToMultiByte(CP_ACP,0,wszTmp,-1,szTmp,10,NULL,NULL);
	m_nSetBacklog=atoi(szTmp);
	if(m_nSetBacklog<1)
	{
		MessageBox(L"backlogֵ����С��1!",L"ERROR",MB_OK);
		return;
	}
	memset(szTmp,0,10);
	memset(wszTmp,0,10);
	GetDlgItemText(IDC_E_SETMAXCLIENT,wszTmp,10);
	WideCharToMultiByte(CP_ACP,0,wszTmp,-1,szTmp,10,NULL,NULL);
	m_nSetMaxClient=atoi(szTmp);
	if(m_nSetMaxClient<1 || m_nSetMaxClient>56)
	{
		MessageBox(L"����������쳣!\n��Чֵ:[1,56]",L"ERROR",MB_OK);
		return;
	}

	memset(szTmp,0,10);
	memset(wszTmp,0,10);
	GetDlgItemText(IDC_E_SETPORT,wszTmp,10);
	WideCharToMultiByte(CP_ACP,0,wszTmp,-1,szTmp,10,NULL,NULL);
	m_nSetPort=atoi(szTmp);
	if(m_nSetPort<1024 || m_nSetPort>65535)
	{
		MessageBox(L"�趨�Ķ˿ں���Ч!\n   (1024,65535)",L"ERROR",MB_OK);
		return;
	}
	CDialogEx::OnOK();
}
