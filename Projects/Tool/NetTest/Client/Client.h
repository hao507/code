
// Client.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CClientApp:
// See Client.cpp for the implementation of this class
//

class CClientApp : public CWinAppEx
{
public:
	CClientApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
	static	void threadFun(MG::Ptr p);
	MG::OneThreadHandle	mThreadHandle;
	static MG::InterLocked mIsStart;
	static MG::InterLocked mIsConnect;
	static CString mStr;

};

extern CClientApp theApp;