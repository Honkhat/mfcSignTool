#pragma once
#include "afxcmn.h"
#include <vector>
using std::vector;

// CClientListDlg �Ի���
struct ClientInfo
{
	wchar_t wszFamily[20];
	wchar_t wszIp[40];
	wchar_t wszPort[20];
	wchar_t wszName[100];
};

class CClientListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientListDlg)

public:
	CClientListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClientListDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CLIENTLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listClient;
	//row count,i.e. client count
	int m_nRow;
	//use the excellent std::VECTOR
	vector<struct ClientInfo> m_vecClient;
	//������紫����ֵ,�Ž�vec��
	void SetListVec(wchar_t* wszFamily, wchar_t* wszIp, wchar_t* wszPort, wchar_t* wszName);

	virtual BOOL OnInitDialog();
};
