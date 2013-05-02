// PeerInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "PeerInfoDlg.h"
#include "afxdialogex.h"


// CPeerInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CPeerInfoDlg, CDialogEx)

CPeerInfoDlg::CPeerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPeerInfoDlg::IDD, pParent)
{

}

CPeerInfoDlg::~CPeerInfoDlg()
{
}

void CPeerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPeerInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CPeerInfoDlg ��Ϣ�������

void CPeerInfoDlg::setUiText(char* szPeerIp,char* szPeerPort,char* szPeerName)
{
	memcpy(m_szPeerIp,szPeerIp,20);
	memcpy(m_szPeerPort,szPeerPort,10);
	memcpy(m_szPeerName,szPeerName,50);
}

BOOL CPeerInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	wchar_t wszTmp[50];
	MultiByteToWideChar(CP_ACP,0,m_szPeerIp,-1,wszTmp,50);
	SetDlgItemText(IDC_E_PEERIP,wszTmp);
	memset(wszTmp,0,50);
	MultiByteToWideChar(CP_ACP,0,m_szPeerPort,-1,wszTmp,50);
	SetDlgItemText(IDC_E_PEERPORT,wszTmp);
	memset(wszTmp,0,50);
	MultiByteToWideChar(CP_ACP,0,m_szPeerName,-1,wszTmp,50);
	SetDlgItemText(IDC_E_PEERNAME,wszTmp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
