// AesToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcSignTool.h"
#include "AesToolDlg.h"
#include "afxdialogex.h"


// CAesToolDlg �Ի���

IMPLEMENT_DYNAMIC(CAesToolDlg, CDialogEx)

CAesToolDlg::CAesToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAesToolDlg::IDD, pParent)
{

}

CAesToolDlg::~CAesToolDlg()
{
}

void CAesToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAesToolDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_ENCODE, &CAesToolDlg::OnBnClickedRadioEncode)
	ON_BN_CLICKED(IDC_RADIO_DECODE, &CAesToolDlg::OnBnClickedRadioDecode)
	ON_BN_CLICKED(IDC_BTN_OPENDOC, &CAesToolDlg::OnBnClickedBtnOpendoc)
	ON_BN_CLICKED(IDC_BTN_SAVEDOC, &CAesToolDlg::OnBnClickedBtnSavedoc)
	ON_BN_CLICKED(IDC_BTN_DOIT, &CAesToolDlg::OnBnClickedBtnDoit)
END_MESSAGE_MAP()


// CAesToolDlg ��Ϣ�������


BOOL CAesToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//--Initialize the values of class MEMBERS begin--
	//default:encode mode
	m_bEncodeMode=true;
	memset(m_szOpenDoc,0,256);
	memset(m_szSaveDoc,0,256);

	//--Initialize the values of class MEMBERS end--
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAesToolDlg::OnBnClickedRadioEncode()
{
	m_bEncodeMode=true;
}


void CAesToolDlg::OnBnClickedRadioDecode()
{
	m_bEncodeMode=false;
}


void CAesToolDlg::OnBnClickedBtnOpendoc()
{
	wchar_t wszOpenFile[MAX_PATH]={0};

	OPENFILENAME OpenFile={0};
	OpenFile.lStructSize=sizeof(OpenFile);
	OpenFile.lpstrFile=wszOpenFile;
	OpenFile.nMaxFile=MAX_PATH;
	OpenFile.lpstrFilter=L"Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	OpenFile.nFilterIndex=1;
	if(::GetOpenFileName(&OpenFile))
	{
		//UpdateData(false)
		SetDlgItemText(IDC_E_OPENDOC,wszOpenFile);
		//wchar-->char
		WideCharToMultiByte(CP_ACP,0,wszOpenFile,-1,m_szOpenDoc,MAX_PATH,NULL,NULL);
	}
}


void CAesToolDlg::OnBnClickedBtnSavedoc()
{
	wchar_t wszSaveFile[MAX_PATH]={0};//������Ҫ��ȡҪ���ܵ��ļ���+�������ܣ���
	OPENFILENAME SaveFile={0};
	SaveFile.lStructSize=sizeof(OPENFILENAME);
	SaveFile.lpstrFile=wszSaveFile;
	SaveFile.nMaxFile=MAX_PATH;
	SaveFile.lpstrFilter=L"Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	SaveFile.lpstrDefExt=L".txt";
	SaveFile.nFilterIndex=1;
	SaveFile.Flags=OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT;
	if(::GetSaveFileName(&SaveFile))
	{
		//UpdateData(false);
		SetDlgItemText(IDC_E_SAVEDOC,wszSaveFile);
		//convey value to class member
		WideCharToMultiByte(CP_ACP,0,wszSaveFile,-1,m_szSaveDoc,MAX_PATH,NULL,NULL);
	}
}


void CAesToolDlg::OnBnClickedBtnDoit()
{
	if(strcmp(m_szOpenDoc,"")==0 || strcmp(m_szSaveDoc,"")==0)
	{
		MessageBox(L"����û��ѡ���ļ�!",L"ERROR",MB_OK);
		return;
	}
	//���ǵ����ܵ����⣬���������;����ʹ�ù̶���ʼ��
	//both Encode Mode and Decode Mode USE this
	byte key[AES::DEFAULT_KEYLENGTH]={0x35,0x8A,0x99,0xFA,0x66,0x3C,0x85,0x5F,0x21,0x3A,0x1D,0x97,0x47,0x39,0x9F,0x78};
	byte iv[AES::DEFAULT_KEYLENGTH]={0x3A,0x33,0x3C,0x37,0x15,0x3E,0xDE,0x6B,0xD5,0xCC,0xEC,0x74,0x59,0x3E,0x6F,0x61};
	string cipher;
	//check which mode current
	if(m_bEncodeMode)
	{
		//-----solid value---------------------
		//������뷨,���������������һ��ʵ��:
		//key: 358A99FA663C855F213A1D9747399F78
        //iv:  3A333C37153EDE6BD5CCEC74593E6F61
		//ע��:key,iv����16�ֽڵ�.����Ҫ�����ϲ�
		//����,�뵽����Ȼ�������,�Լ��������:
		//key:1234567890abcdef
		//iv: abcdef0987654321
		//���:unknown.
		//-----solid value---------------------
		
		try
		{
			CBC_Mode< AES >::Encryption en;
			en.SetKeyWithIV(key, sizeof(key), iv);

			// The StreamTransformationFilter removes
			//  padding as required.
			FileSource f(m_szOpenDoc, true, 
				new StreamTransformationFilter(en,
				new StringSink(cipher)
				) // StreamTransformationFilter
				); // StringSource
			//cipher-->m_szSaveDoc
			StringSource(cipher,true,new FileSink(m_szSaveDoc));
		}
		catch(const CryptoPP::Exception& en)
		{
			MessageBox(L"AES�����쳣!",L"ERROR",MB_OK);
			return;
		}

	}
	//Decode Mode
	else
	{
		try
		{
			CBC_Mode< AES >::Decryption de;
			de.SetKeyWithIV(key, sizeof(key), iv);

			// The StreamTransformationFilter removes
			//  padding as required.
			//m_szOpenDoc-->cipher
			FileSource(m_szOpenDoc,true,new StringSink(cipher));
			//decrypt begin..
			StringSource (cipher, true, 
				new StreamTransformationFilter(de,
				new FileSink(m_szSaveDoc)
				) // StreamTransformationFilter
				); // StringSource
		}
		catch(const CryptoPP::Exception& de)
		{
			MessageBox(L"AES�����쳣!",L"ERROR",MB_OK);
			return;
		}
	}
	MessageBox(L"SUCCESS",L"Congratulations!",MB_OK);
}
