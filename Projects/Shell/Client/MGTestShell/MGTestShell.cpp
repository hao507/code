// MGTestShell.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Debug_def.h"
int shellApp()
{
	MG::DllLoader dllLoader;
	MG::IClientMain* clientInterface = NULL;

	GET_MGCLIENT_INTERFACE_PROC proc; 
	std::wstring dllName;
#ifdef _DEBUG
	dllName = L"Core\\MGClient_d.dll";
#else
	dllName = L"Core\\MGClient.dll";
#endif

	if (dllLoader.load(dllName.c_str(),false)) 
	{ 
		proc = (GET_MGCLIENT_INTERFACE_PROC) dllLoader.getProcAddress("GET_MGCLIENT_INTERFACE"); 
		if (NULL != proc) 
		{
			clientInterface = (MG::IClientMain*)proc(); 
			if (clientInterface==NULL)
			{
				MG::MsgBox::show("Load IClientMain Failed!");
				return 0;
			}
		}else
		{
			MG::MsgBox::show("Don't Find IClientMain Entry!");
			return 0;
		}
	}else
	{
		MG::MsgBox::show("Don't Load MGClient DLL!");
		return 0;
	}

	if ( clientInterface->initialize() )
	{
		clientInterface->run();
	}
	clientInterface->uninitialize();
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
#else
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hConsole)
	{
		FreeConsole();
	}
#endif


	//MG::InstallMyExceptHandle();
	MG_EXCEPTION_BEGIN
	return shellApp();
	MG_EXCEPTION_END("MGTestShell-_tmain");
	MG::UnInstallMyExceptHandle();
	return 0;
}

