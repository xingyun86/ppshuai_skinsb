
// SkinSbDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSkinSbDemoApp:
// �йش����ʵ�֣������ SkinSbDemo.cpp
//

class CSkinSbDemoApp : public CWinAppEx
{
public:
	CSkinSbDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

	virtual int ExitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSkinSbDemoApp theApp;