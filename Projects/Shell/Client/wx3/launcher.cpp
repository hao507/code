// luancher.cpp : Defines the entry point for the application.
////////////////////////////////////////////////////////////////////////////

#include "launcher.h"
////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------
bool LuancherApp :: OnInit () 
{ 
	// 创建主窗口 
	wxSkinSimpleFrame *mFrame = new wxSkinSimpleFrame ( NULL, -1, _T("英雄志 Launcher")); 

	mIe = new wxIEHtmlWin(mFrame, -1,wxPoint(25,202), wxSize(358,223),wxBORDER_NONE);
	mIe->LoadUrl(_T("http://cms2.kx1d.com/html/yxz/yxz_news/"));
	mIe->ClearBackground();

	// 显示主窗口 
	 
	mMainEngine = new wxSkinEngine();
	mMainEngine->Load(_T("I:/MG/Project/MGCode/Projects/Shell/Client/Launcher/Debug/res/mainSkin.xml"));
	// 开始事件处理循环 

	mMainEngine->AssignControl(wxT("LauncherFrame"), mFrame);
	mFrame->Show();
	mFrame->Refresh();	
	mFrame->Centre();
	return true ; 
} 
//------------------------------------------------------------------------------------------------
int LuancherApp::OnExit()
{
	return(wxApp::OnExit());
}
//------------------------------------------------------------------------------------------------