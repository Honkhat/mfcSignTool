#pragma once
//for open file
#include <ShlObj.h>
//for aes
#include <string>
using std::string;
#include <fstream>
using std::fstream;
#include <iostream>
using std::ios;
#include <filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
#include <aes.h>
using CryptoPP::AES;
#include <ccm.h>
using CryptoPP::CBC_Mode;
#include <files.h>
using CryptoPP::FileSource;
using CryptoPP::FileSink;
// CAesToolDlg �Ի���

class CAesToolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAesToolDlg)

public:
	CAesToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAesToolDlg();

// �Ի�������
	enum { IDD = IDD_DLG_AESTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//current mode
	bool m_bEncodeMode;
	//the specified file
	char m_szOpenDoc[MAX_PATH];
	char m_szSaveDoc[MAX_PATH];
	
	//���ǵ����ܵ����⣬���������;����ʹ�ù̶���ʼ��

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioEncode();
	afx_msg void OnBnClickedRadioDecode();
	afx_msg void OnBnClickedBtnOpendoc();
	afx_msg void OnBnClickedBtnSavedoc();
	afx_msg void OnBnClickedBtnDoit();
};
