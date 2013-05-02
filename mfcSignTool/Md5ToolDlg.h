#pragma once
#include <ShlObj.h>
#include <md5.h>
using CryptoPP::MD5;
#include <files.h>
using CryptoPP::FileSource;
using CryptoPP::HashFilter;
using CryptoPP::ArraySink;
#include <hex.h>
using CryptoPP::HexEncoder;
#include <string>
using std::string;
// CMd5ToolDlg �Ի���

class CMd5ToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMd5ToolDlg)

public:
	CMd5ToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMd5ToolDlg();

// �Ի�������
	enum { IDD = IDD_DLG_MD5TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenfile();
public:
	//filename that md5 for
	char m_szFileName[256];
	afx_msg void OnBnClickedBtnCalc();
};
