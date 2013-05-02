// ClientListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "ClientListDlg.h"
#include "afxdialogex.h"


// CClientListDlg �Ի���

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


// CClientListDlg ��Ϣ�������


BOOL CClientListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Initialize class members
	m_nRow=1;
	//Initialize ListCtrl
	LONG lStyle;
	lStyle = GetWindowLong(m_listClient.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listClient.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listClient.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listClient.SetExtendedStyle(dwStyle); //������չ���

	m_listClient.InsertColumn( 0, L"��ַЭ��", LVCFMT_CENTER, 100 );//������
    m_listClient.InsertColumn( 1, L"IP��ַ", LVCFMT_CENTER, 100 );
	m_listClient.InsertColumn( 2, L"�˿ں�", LVCFMT_CENTER, 100 );
	m_listClient.InsertColumn( 3, L"������", LVCFMT_CENTER, 100 );

	int nRow=0;
	for(int i=0;i<m_vecClient.size();i++)
	{
		nRow = m_listClient.InsertItem(i,L"");//������
		m_listClient.SetItemText(nRow,0,m_vecClient[i].wszFamily);//��������
		m_listClient.SetItemText(nRow,1,m_vecClient[i].wszIp);
		m_listClient.SetItemText(nRow,2,m_vecClient[i].wszPort);
		m_listClient.SetItemText(nRow,3,m_vecClient[i].wszName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
