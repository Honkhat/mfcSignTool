#pragma once
#include "afxcmn.h"
#include <vector>
using std::vector;

// CClientListDlg 对话框
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
	CClientListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientListDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CLIENTLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listClient;
	//row count,i.e. client count
	int m_nRow;
	//use the excellent std::VECTOR
	vector<struct ClientInfo> m_vecClient;
	//接收外界传来的值,放进vec里
	void SetListVec(wchar_t* wszFamily, wchar_t* wszIp, wchar_t* wszPort, wchar_t* wszName);

	virtual BOOL OnInitDialog();
};
