// MAJIANG.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMAJIANGApp:
// �йش����ʵ�֣������ MAJIANG.cpp
//

class CMAJIANGApp : public CWinApp
{
public:
	CMAJIANGApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMAJIANGApp theApp;
