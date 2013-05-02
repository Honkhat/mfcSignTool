// Md5ToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "Md5ToolDlg.h"
#include "afxdialogex.h"


// CMd5ToolDlg 对话框

IMPLEMENT_DYNAMIC(CMd5ToolDlg, CDialogEx)

CMd5ToolDlg::CMd5ToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMd5ToolDlg::IDD, pParent)
{

}

CMd5ToolDlg::~CMd5ToolDlg()
{
}

void CMd5ToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMd5ToolDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CMd5ToolDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_CALC, &CMd5ToolDlg::OnBnClickedBtnCalc)
END_MESSAGE_MAP()


// CMd5ToolDlg 消息处理程序


void CMd5ToolDlg::OnBnClickedBtnOpenfile()
{
	wchar_t wszOpenFile[MAX_PATH]={0};

	OPENFILENAME OpenFile={0};
	OpenFile.lStructSize=sizeof(OpenFile);
	OpenFile.lpstrFile=wszOpenFile;
	OpenFile.nMaxFile=MAX_PATH;
	OpenFile.lpstrFilter=L"Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	OpenFile.nFilterIndex=2;
	if(::GetOpenFileName(&OpenFile))
	{
		//UpdateData(false)
		SetDlgItemText(IDC_E_OPENFILE,wszOpenFile);
		//wchar-->char
		WideCharToMultiByte(CP_ACP,0,wszOpenFile,-1,m_szFileName,256,NULL,NULL);
	}
}


void CMd5ToolDlg::OnBnClickedBtnCalc()
{
	if(strcmp(m_szFileName,"")==0)
	{
		MessageBox(L"文件名不可为空!",L"ERROR",MB_OK);
		return;
	}
	MD5 hash;
	byte buffer[2*MD5::DIGESTSIZE];
	FileSource (m_szFileName,true,new HashFilter(hash,new HexEncoder(new ArraySink(buffer,2*MD5::DIGESTSIZE))));
	string str_md5((const char*)buffer,2*MD5::DIGESTSIZE);
	//char-->wchar_t
	CString csTmp;
	csTmp+=str_md5.c_str();
	SetDlgItemText(IDC_E_MD5,csTmp);	
}
