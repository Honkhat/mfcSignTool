#pragma once
//hj added
#include <WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
//md5 related
#include <sstream>
using namespace std;
#include <string>

#include <hex.h>
using CryptoPP::HexEncoder;
#include <files.h>
using CryptoPP::FileSource;
using CryptoPP::ArraySink;
#include <md5.h>
using CryptoPP::MD5;
using CryptoPP::HashFilter;
#include <integer.h>
using CryptoPP::Integer;
//openfile related
#include <ShlObj.h>

// CClientDlg 对话框

class CClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientDlg)

public:
	CClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClientDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatusBarCtrl m_barClient;
	SOCKET m_sockClient;
	//status:whether connected (server) or not
	bool m_bConnect;
	//--md5 related begin--
	//the doc name that md5 for
	char m_szFileSpec[MAX_PATH];
	//the md5
	string m_strMd5Spec;   //md5 value for m_szFileSpec
	Integer m_nK;          //blind factor
	Integer m_nE;          //public key
	Integer m_nN;          //Big Integer
	Integer m_nSs;         //Sign received blinded
	Integer m_nS;          //real Signature from Bob
	//--md5 related over--

	virtual BOOL OnInitDialog();
	//Function: create a socket and connect server
	bool CreateAndConn(char* szAddr,unsigned int nPort);
	//shut connect down
	void ShutConn();
	//calculate the md5 for specific file
	//[in]:szFileName;[out]:sMd5
	void CalcMd5ForFile(char* szFilaName,string& strMd5);

	afx_msg void OnBnClickedRadioSend();
	afx_msg void OnBnClickedRadioRecv();
	//--vital---
	afx_msg long OnSocket(WPARAM wParam,LPARAM lParam);
	//--vital---
	afx_msg void OnBnClickedBtnGetp();
	afx_msg void OnBnClickedBtnAsk();
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnBnClickedBtnUnblind();
	afx_msg void OnBnClickedBtnVerify();
};
