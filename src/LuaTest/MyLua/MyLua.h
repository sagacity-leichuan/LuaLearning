
// MyLua.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyLuaApp: 
// �йش����ʵ�֣������ MyLua.cpp
//

class CMyLuaApp : public CWinApp
{
public:
	CMyLuaApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyLuaApp theApp;