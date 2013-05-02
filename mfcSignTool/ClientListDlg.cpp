// ClientListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientListDlg.h"
#include "afxdialogex.h"


// CClientListDlg 对话框

IMPLEMENT_DYNAMIC(CClientListDlg, CDialogEx)

CClientListDlg::CClientListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientListDlg::IDD, pParent)
{

}

CClientListDlg::~CClientListDlg()
{
}

void CClientListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listClient);
}


BEGIN_MESSAGE_MAP(CClientListDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientListDlg 消息处理程序


BOOL CClientListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Initialize class members
	m_nRow=1;
	//Initialize ListCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listClient.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listClient.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listClient.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listClient.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listClient.InsertColumn( 0, L"地址协议", LVCFMT_CENTER, 100 );//插入列
    m_listClient.InsertColumn( 1, L"IP地址", LVCFMT_CENTER, 100 );
	m_listClient.InsertColumn( 2, L"端口号", LVCFMT_CENTER, 100 );
	m_listClient.InsertColumn( 3, L"主机名", LVCFMT_CENTER, 100 );

	int nRow=0;
	for(int i=0;i<m_vecClient.size();i++)
	{
		nRow = m_listClient.InsertItem(i,L"");//插入行
		m_listClient.SetItemText(nRow,0,m_vecClient[i].wszFamily);//设置数据
		m_listClient.SetItemText(nRow,1,m_vecClient[i].wszIp);
		m_listClient.SetItemText(nRow,2,m_vecClient[i].wszPort);
		m_listClient.SetItemText(nRow,3,m_vecClient[i].wszName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CClientListDlg::SetListVec(wchar_t* wszFamily, wchar_t* wszIp, wchar_t* wszPort, wchar_t* wszName)
{
	struct ClientInfo egClient;
	memset(&egClient,0,sizeof(ClientInfo));
	memcpy(egClient.wszFamily,wszFamily,20);
	memcpy(egClient.wszIp,wszIp,40);
	memcpy(egClient.wszPort,wszPort,20);
	memcpy(egClient.wszName,wszName,100);
		
	m_vecClient.push_back(egClient);
}
