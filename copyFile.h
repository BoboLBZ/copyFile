
// copyFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CcopyFileApp: 
// �йش����ʵ�֣������ copyFile.cpp
//

class CcopyFileApp : public CWinApp
{
public:
	CcopyFileApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CcopyFileApp theApp;
