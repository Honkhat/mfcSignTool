#pragma once


// CHowDlg �Ի���

class CHowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHowDlg)

public:
	CHowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHowDlg();

// �Ի�������
	enum { IDD = IDD_DLG_HOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
