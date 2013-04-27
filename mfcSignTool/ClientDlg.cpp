// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


// CClientDlg 对话框

IMPLEMENT_DYNAMIC(CClientDlg, CDialogEx)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{

}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_SEND, &CClientDlg::OnBnClickedRadioSend)
	ON_BN_CLICKED(IDC_RADIO_RECV, &CClientDlg::OnBnClickedRadioRecv)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序


BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//set default mode
	CheckRadioButton(IDC_RADIO_SEND,IDC_RADIO_RECV,IDC_RADIO_SEND);
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(false);
	GetDlgItem(IDC_E_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CClientDlg::OnBnClickedRadioSend()
{
	//unenable and invisible the recv-mode stuff
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->EnableWindow(false);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->EnableWindow(false);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(false);
	GetDlgItem(IDC_E_VERIFY)->EnableWindow(false);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(false);
	//enable and visible my-mode stuff
	GetDlgItem(IDC_E_P)->ShowWindow(true);
	GetDlgItem(IDC_BTN_GETP)->EnableWindow(true);
	GetDlgItem(IDC_BTN_GETP)->ShowWindow(true);
	GetDlgItem(IDC_E_OPENFILE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_OPENFILE)->EnableWindow(true);
	GetDlgItem(IDC_BTN_OPENFILE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_ASK)->EnableWindow(true);
	GetDlgItem(IDC_BTN_ASK)->ShowWindow(true);
}


void CClientDlg::OnBnClickedRadioRecv()
{
	//unenable and invisible the send-mode stuff
	GetDlgItem(IDC_E_P)->EnableWindow(false);
	GetDlgItem(IDC_E_P)->ShowWindow(false);
	GetDlgItem(IDC_BTN_GETP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_GETP)->ShowWindow(false);
	GetDlgItem(IDC_E_OPENFILE)->EnableWindow(false);
	GetDlgItem(IDC_E_OPENFILE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_OPENFILE)->EnableWindow(false);
	GetDlgItem(IDC_BTN_OPENFILE)->ShowWindow(false);
	GetDlgItem(IDC_BTN_ASK)->EnableWindow(false);
	GetDlgItem(IDC_BTN_ASK)->ShowWindow(false);
	//enable and visible my-mode stuff
	GetDlgItem(IDC_SE_RECVSTATE)->EnableWindow(true);
	GetDlgItem(IDC_SE_RECVSTATE)->ShowWindow(true);
	GetDlgItem(IDC_E_RECVSTATE)->ShowWindow(true);
	GetDlgItem(IDC_BTN_UNBLIND)->EnableWindow(true);
	GetDlgItem(IDC_BTN_UNBLIND)->ShowWindow(true);
	GetDlgItem(IDC_E_UNBLIND)->ShowWindow(true);
	GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(true);
	GetDlgItem(IDC_BTN_VERIFY)->ShowWindow(true);
	GetDlgItem(IDC_E_VERIFY)->ShowWindow(true);
}
