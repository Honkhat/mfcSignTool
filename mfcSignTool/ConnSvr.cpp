// ConnSvr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ConnSvr.h"
#include "afxdialogex.h"


// CConnSvr �Ի���

IMPLEMENT_DYNAMIC(CConnSvr, CDialogEx)

CConnSvr::CConnSvr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnSvr::IDD, pParent)
{

}

CConnSvr::~CConnSvr()
{
}

void CConnSvr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnSvr, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConnSvr::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnSvr ��Ϣ�������


void CConnSvr::OnBnClickedOk()
{
	//get the input value
	wchar_t wcTmp[20]={0};
	GetDlgItemText(IDC_E_IPSVR,wcTmp,20);
	WideCharToMultiByte(CP_ACP,0,wcTmp,-1,m_szIpSvr,20,NULL,NULL);
	if(strcmp(m_szIpSvr,"")==0)
	{
		MessageBox(L"IP��ַ����Ϊ��!",L"����",MB_OK);
		return;
	}

	char szPort[20]={0};
	memset(wcTmp,0,20);
	GetDlgItemText(IDC_E_PORTSVR,wcTmp,20);
	WideCharToMultiByte(CP_ACP,0,wcTmp,-1,szPort,20,NULL,NULL);
	m_nPort=atoi(szPort);
	if(m_nPort<1024||m_nPort>65535)
	{
		MessageBox(L"�˿ںŴ���!��Ч����:(1024,65535)",L"����",MB_OK);
		return;
	}

	CDialogEx::OnOK();
}
