
// mfcSignTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcSignToolApp:
// �йش����ʵ�֣������ mfcSignTool.cpp
//

class CmfcSignToolApp : public CWinApp
{
public:
	CmfcSignToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcSignToolApp theApp;