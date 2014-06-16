// luancher.cpp : Defines the entry point for the application.
////////////////////////////////////////////////////////////////////////////

#include "launcher.h"
#include "LiveUpdate.hpp"
#include "config.h"
#include "MyThread.h"
/*#include "MGFile.h"
#include "MGMath.h"*/


#include "MGTypes.h"
#include "MGDefine.h"


#include "MGMisc.h"
//#include "MGMemory.h"
//#include "MGDB.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGClientInterface.h"
////////////////////////////////////////////////////////////////////////////
IMPLEMENT_APP( LauncherApp )
//IMPLEMENT_CLASS( LauncherApp, wxApp )
BEGIN_EVENT_TABLE( LauncherApp, wxApp )
EVT_BUTTON(EVENT_ID_BTNFREEREGISTRATION,LauncherApp::OnBtnFreeRegistration)
EVT_BUTTON(EVENT_ID_BTNRECHARGE,		LauncherApp::OnBtnRecharge)
EVT_BUTTON(EVENT_ID_BTNOFFICIALWEBSITE, LauncherApp::OnBtnOfficialWebsite)
EVT_BUTTON(EVENT_ID_BTNOFFICIALFORUM,	LauncherApp::OnBtnOfficialForum)
EVT_BUTTON(EVENT_ID_BTNGAMESETTING,		LauncherApp::OnBtnGameSetting)
EVT_BUTTON(EVENT_ID_BTNDOWNLOAD,		LauncherApp::OnBtnDownload)
EVT_BUTTON(EVENT_ID_BTNVERCAPTION,		LauncherApp::OnBtnVerCaption)
EVT_BUTTON(EVENT_ID_BTNGAMEREPAIR,		LauncherApp::OnBtnGameRepair)
EVT_BUTTON(EVENT_ID_BTNMANUALUPDATE,	LauncherApp::OnBtnManualUpdate)
EVT_BUTTON(EVENT_ID_BTNGAMESTART,		LauncherApp::OnBtnGameStart)
EVT_BUTTON(EVENT_ID_BTNEXIT,			LauncherApp::OnBtnExit)
EVT_IDLE(LauncherApp::OnIdle)
END_EVENT_TABLE()

using namespace MG;
//------------------------------------------------------------------------------------------------
bool LauncherApp :: OnInit () 
{ 
#ifndef __WXMAC__
	wxFileName fname (wxApp::argv[0]);
	fname.MakeAbsolute();
	mDir = fname.GetPath();
#else
	mDir = wxFileName::GetCwd();
#endif

	Config::getInstance().load((mDir + _T("\\launcher\\launcher.ini")));

	mExit = false;
	mPachSize = 0;
	mPachSize = 0;
	mDownSize = 0;
	mTempDownSize = 0;

	// UI
	////////////////////////////////////////////////////////////
	mMainEngine = new wxSkinEngine();
	mMainEngine->Load(mDir + _T("/launcher/mgData.dat"),_T("mainSkin.xml"));
	// 创建主窗口 
	mMainFrame = new wxSkinSimpleFrame ( NULL, -1, _T("英雄志 Launcher")); 

	// IE
	mIe = new wxIEHtmlWin(mMainFrame, -1,wxPoint(70,73), wxSize(380,150),wxBORDER_NONE);
	mIe->LoadString(wxString("<html>\n \
					 <FRAMESET COLS=\"100%\" frameborder=\"NO\" border=\"0\" framespacing=\"0\" style=\"border:2px #000000 solid\">\n \
					 <FRAME SRC=\"http://cms2.kx1d.com/html/yxz/yxz_news/\"\n \
					 name=\"DisplayManager\" SCROLLING=\"NO\">\n</FRAMESET>\n \
					 </html>\n"));
	mIe->ClearBackground();


	mProcessCurr = new wxGauge(mMainFrame,-1, 100, wxPoint(61,259), wxSize(510,10), wxGA_HORIZONTAL|wxGA_SMOOTH|wxBORDER_NONE);
	mProcessCurr->SetForegroundColour(wxColour(194,123,0,0));
	mProcessCurr->SetBackgroundColour(wxColour(21,56,85,wxALPHA_TRANSPARENT));

	mProcessAll = new wxGauge(mMainFrame,-1, 100, wxPoint(61,277), wxSize(510,10), wxGA_HORIZONTAL|wxGA_SMOOTH|wxBORDER_NONE);
	mProcessAll->SetForegroundColour(wxColour(194,123,0,0));
	mProcessAll->SetBackgroundColour(wxColour(21,56,85,wxALPHA_TRANSPARENT));

	wxFont font = mMainFrame->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(11);
	

	mBtnFreeRegistration	= new wxSkinButton(mMainFrame, EVENT_ID_BTNFREEREGISTRATION	);
	mBtnRecharge			= new wxSkinButton(mMainFrame, EVENT_ID_BTNRECHARGE			);
	mBtnOfficialWebsite		= new wxSkinButton(mMainFrame, EVENT_ID_BTNOFFICIALWEBSITE	);
	mBtnOfficialForum		= new wxSkinButton(mMainFrame, EVENT_ID_BTNOFFICIALFORUM	);
	mBtnGameSetting			= new wxSkinButton(mMainFrame, EVENT_ID_BTNGAMESETTING		);
	mBtnDownload			= new wxSkinButton(mMainFrame, EVENT_ID_BTNDOWNLOAD			);
	mBtnVerCaption			= new wxSkinButton(mMainFrame, EVENT_ID_BTNVERCAPTION		);
	mBtnGameRepair			= new wxSkinButton(mMainFrame, EVENT_ID_BTNGAMEREPAIR		);
	mBtnManualUpdate		= new wxSkinButton(mMainFrame, EVENT_ID_BTNMANUALUPDATE		);
	mBtnGameStart			= new wxSkinButton(mMainFrame, EVENT_ID_BTNGAMESTART		);						 
	mBtnExit				= new wxSkinButton(mMainFrame, EVENT_ID_BTNEXIT				);
	mStaticCurrVer			= new wxStaticText(mMainFrame, EVENT_ID_STATICCURRVER,_T(""));
	mStaticNewVer			= new wxStaticText(mMainFrame, EVENT_ID_STATICNEWVER,_T("")	);
	mStaticVerDesc			= new wxStaticText(mMainFrame, EVENT_ID_STATICVERDESC,_T(""));

	/*mBtnFreeRegistration->SetLabel(		_T("免费注册"));
	mBtnRecharge->SetLabel(				_T("购卡充值"));
	mBtnOfficialWebsite->SetLabel(		_T("官方网站"));
	mBtnOfficialForum->SetLabel(		_T("官方论坛"));
	mBtnGameSetting->SetLabel(			_T("游戏设置"));
	mBtnDownload->SetLabel(				_T("游戏下载"));
	mBtnVerCaption->SetLabel(			_T("版本说明"));
	mBtnGameRepair->SetLabel(			_T("游戏修复"));
	mBtnManualUpdate->SetLabel(			_T("手动更新"));
	,_T("免费注册") ,wxPoint(456,77),wxSize(104,24)
	,_T("购卡充值") ,wxPoint(456,107),wxSize(104,24
	,_T("官方网站") ,wxPoint(456,137),wxSize(104,24
	,_T("官方论坛") ,wxPoint(456,167),wxSize(104,24
	,_T("游戏设置") ,wxPoint(456,197),wxSize(104,24
	,_T("游戏下载") ,wxPoint(130,294),wxSize(76,30)
	,_T("版本说明") ,wxPoint(222,294),wxSize(76,30)
	,_T("游戏修复") ,wxPoint(314,294),wxSize(76,30)
	,_T("手动更新") ,wxPoint(406,294),wxSize(76,30)
	*/

	//mBtnGameStart->SetLabel(_T("开始游戏"));

	mMainEngine->AssignControl(wxT("LauncherFrame"			), mMainFrame			);
	mMainEngine->AssignControl(wxT("mBtnFreeRegistration"	), mBtnFreeRegistration	);
	mMainEngine->AssignControl(wxT("mBtnRecharge"			), mBtnRecharge			);
	mMainEngine->AssignControl(wxT("mBtnOfficialWebsite"	), mBtnOfficialWebsite	);
	mMainEngine->AssignControl(wxT("mBtnOfficialForum"		), mBtnOfficialForum	);
	mMainEngine->AssignControl(wxT("mBtnGameSetting"		), mBtnGameSetting		);
	mMainEngine->AssignControl(wxT("mBtnDownload"			), mBtnDownload			);
	mMainEngine->AssignControl(wxT("mBtnVerCaption"			), mBtnVerCaption		);
	mMainEngine->AssignControl(wxT("mBtnGameRepair"			), mBtnGameRepair		);
	mMainEngine->AssignControl(wxT("mBtnManualUpdate"		), mBtnManualUpdate		);
	mMainEngine->AssignControl(wxT("mBtnGameStart"			), mBtnGameStart		);
	mMainEngine->AssignControl(wxT("mBtnExit"				), mBtnExit				);
	
	//mMainEngine->AssignControl(wxT("mStaticCurrVer"			), mStaticCurrVer		);
	//mMainEngine->AssignControl(wxT("mStaticNewVer"			), mStaticNewVer		);
	//mMainEngine->AssignControl(wxT("mStaticVerDesc"			), mStaticVerDesc		);
	
	/*mBtnFreeRegistration->SetSize(	456,77,	104,24,wxSIZE_FORCE);		
	mBtnRecharge->SetSize(			456,107,104,24,wxSIZE_FORCE);		
	mBtnOfficialWebsite->SetSize(	456,137,104,24,wxSIZE_FORCE);		
	mBtnOfficialForum->SetSize(		456,167,104,24,wxSIZE_FORCE);	
	mBtnGameSetting->SetSize(		456,197,104,24,wxSIZE_FORCE);

	mBtnDownload->SetSize(			130,294,76,30,wxSIZE_FORCE);				
	mBtnVerCaption->SetSize(		222,294,76,30,wxSIZE_FORCE);			
	mBtnGameRepair->SetSize(		314,294,76,30,wxSIZE_FORCE);		
	mBtnManualUpdate->SetSize(		406,294,76,30,wxSIZE_FORCE);			
	mBtnGameStart->SetSize(			483,294,76,30,wxSIZE_FORCE);*/	
				
	mStaticCurrVer->SetSize(60,236,150,16);			
	mStaticNewVer->SetSize(210,236,150,16);		
	mStaticVerDesc->SetSize(460,236,150,16);

	//版本 设置字体 大小
	wxFont font1 = mStaticCurrVer->GetFont();
	font1.SetWeight(wxNORMAL);
	font1.SetPointSize(9);
	mStaticCurrVer->SetFont(font1);
	mStaticCurrVer->SetOwnBackgroundColour(wxColor(0,0,0,0));
	mStaticCurrVer->SetForegroundColour(wxColor(255,255,255));

	wxFont font2 = mStaticNewVer->GetFont();
	font2.SetWeight(wxNORMAL);
	font2.SetPointSize(9);
	mStaticNewVer->SetFont(font2);
	mStaticNewVer->SetOwnBackgroundColour(wxColor(0,0,0,0));
	mStaticNewVer->SetForegroundColour(wxColor(255,255,255));

	wxFont font3 = mStaticVerDesc->GetFont();
	font3.SetWeight(wxNORMAL);
	font3.SetPointSize(9);
	mStaticVerDesc->SetFont(font3);
	mStaticVerDesc->SetOwnBackgroundColour(wxColor(0,0,0,0));
	mStaticVerDesc->SetForegroundColour(wxColor(255,255,255));
	
	mProcessCurr->SetValue(0);
	mProcessAll->SetValue(0);

	enableStartWindow(false);

	// 打包工具
	////////////////////////////////////////////////////////////
	mPacketUpdateMgr = new MG::MGPackUpdateManager();

	///UpdateThread
	////////////////////////////////////////////////////////////
	/*mUpdateVersionThread = new MyThread(this,updateVersion);
	if (mUpdateVersionThread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError("Can't create the thread!");
		delete mUpdateVersionThread;
		mUpdateVersionThread = NULL;
	}
	else
	{
		if (mUpdateVersionThread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete mUpdateVersionThread;
			mUpdateVersionThread = NULL;
		}
		else
		{
		}
	}*/

	if (Config::getInstance().isUpdate())
	{
		mUpdateVersionThread1.create(updateVersion,(Ptr)this);
	}
	else
	{
		enableStartWindow(true);
	}
	
	


	mMainEngine->InitializeSkin();

	SetTopWindow(mMainFrame);
	mMainFrame->SetSize(740,426);
	mMainFrame->Show();
	mMainFrame->Refresh();	
	mMainFrame->Centre();

	
	return true ; 
} 
//------------------------------------------------------------------------------------------------
int LauncherApp::OnExit()
{
	if (mMainEngine)
	{
		delete mMainEngine;
	}
	return(wxApp::OnExit());
}

void LauncherApp::skip( wxMouseEvent& event )
{
	int i = event.GetButton();	
	event.Skip();
}

//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnExit( wxCommandEvent &event )
{
	Exit();
}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnGameStart( wxCommandEvent &event )
{
	enableStartWindow(false);
	if (!mGameThread1.create(gameRun,(Ptr)this))
	{
		enableStartWindow(true);
	}
	
}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnManualUpdate( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnGameRepair( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnVerCaption( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnDownload( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnGameSetting( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnOfficialForum( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnOfficialWebsite( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnRecharge( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
void LauncherApp::OnBtnFreeRegistration( wxCommandEvent &event )
{

}
//------------------------------------------------------------------------------------------------
bool LauncherApp::checkVersion()
{
	bool chk;
	CLiveUpdate& update = CLiveUpdate::getSingleton();
	if (update.initialize() != false)
	{
		chk = update.setUpdateVersion(Config::getInstance().getVersionPath().c_str(),Config::getInstance().getCurrVersion().c_str());

		if (chk == false)
		{
			wxMessageBox(_T("服务器未开启，下载失败"),_T("系统提示"));
			return false;
		}
		
		wxString version = update.getLatestVersion();
		if (Config::getInstance().getCurrVersion().compare(version) == 0)
		{
			setCurrProcessVal(100);
			setWholeProcessVal(100);
			setVersion(version,version);
			return true;
		}
		setVersion(Config::getInstance().getCurrVersion(),version);
		while (update.checkLiveUpdate() != false)
		{
			update.destroy();
#ifdef _DEBUG
			::DeleteFileA("luancher/liveUpdate_d.dll");
			::MoveFileA("luancher/liveUpdate_d.dll", "liveUpdate_d.dll");
#else
			::DeleteFileA("luancher/liveUpdate.dll");
			::MoveFileA("luancher/liveUpdate.dll", "liveUpdate.dll");
#endif

			if (update.initialize() != false)
			{
				chk = update.setUpdateVersion(Config::getInstance().getVersionPath().c_str(),Config::getInstance().getCurrVersion().c_str());
				break;
			}
			break;
		}
	}
	update.setUpdateManager(&update);
	update.setLiveUpdateProcess(liveUpdateProcess);
	chk = update.updateResource();

	printf("当前版本号:%d\n", update.getCurrentVersion());
	update.destroy();

	return true;
}
//------------------------------------------------------------------------------------------------
void LauncherApp::liveUpdateProcess( const char* lpszFile, int downLoadSize,float fPercent,bool bIsFinished ,void* manager)
{
	LauncherApp& app = wxGetApp();
	CLiveUpdate* update = (CLiveUpdate*)manager;

	
	app.mPachSize = update->getCurrPatchSize();
	
	if (bIsFinished)
	// 当前补丁下载完毕
	{	
		if (lpszFile != NULL)
		// 当前版本未完成
		{
			app.mTempDownSize = 0;
			app.mDownSize += downLoadSize;
			app.setCurrProcessVal(100);
			app.setWholeProcessVal(((float)app.mDownSize / app.mPachSize) * 100);

			if (app.getPackUpdateMgr()->resUpdate(lpszFile,"launcher/tempdown","","launcher/tempclient"))
			{
				app.setVersion(update->getCurrentVersion(),update->getLatestVersion());
			}
			else
			{
				// 并包失败
				wxASSERT(_("并包失败"));
			}
			wxString strDir = lpszFile;
			int pos = strDir.find_last_of('/');
			strDir = strDir.substr(0,pos);
			app.getPackUpdateMgr()->deleteTempFolder(strDir);
			app.getPackUpdateMgr()->deleteTempFolder("launcher/tempdown");
			app.getPackUpdateMgr()->deleteTempFolder("launcher/tempclient");
		}
		else
		// 当前版本完成
		{
			if(!app.setVersion(update->getCurrentVersion(),update->getLatestVersion()))
			{
				app.setCurrProcessVal(0);
				app.setWholeProcessVal(0);
			}
			else
			{
				app.setCurrProcessVal(100);
				app.setWholeProcessVal(100);
			}
		}
	}
	else
	{
		app.mTempDownSize = downLoadSize; 
		app.setCurrProcessVal(fPercent * 100);
		app.setWholeProcessVal(((float)(app.mDownSize + app.mTempDownSize)) / app.mPachSize * 100);
	}
}

void LauncherApp::setWholeProcessVal( int val )
{
	mProcessAll->SetValue(val);
}

void LauncherApp::setCurrProcessVal( int val )
{
	mProcessCurr->SetValue(val);
}

void LauncherApp::enableStartWindow( bool enable )
{
	mBtnGameStart->Enable(enable);
	if (enable)
		mBtnGameStart->ShowNormalSkin();
	else	
		mBtnGameStart->SetStateFlag(3);
}

MG::MGPackUpdateManager* LauncherApp::getPackUpdateMgr()
{
	return mPacketUpdateMgr;
}

bool LauncherApp::setVersion( wxString& currVersion,wxString& latestVersion )
{
	Config::getInstance().setCurrVersion(currVersion);
	Config::getInstance().save();
	mStaticCurrVer->SetLabel(_T("当前版本") + currVersion);
	mStaticNewVer->SetLabel(_T("最新版本") + latestVersion);
	if (currVersion.compare(latestVersion) == 0)
	{
		mStaticVerDesc->SetLabel(_T("当前已是最新版本"));
		enableStartWindow(true);
		return true;
	}
	return false;

}

void LauncherApp::updateVersion( MG::Ptr manager )
{
	OneThreadHandle* thd = (OneThreadHandle*)manager;
	if (!thd)
	{
		wxASSERT(false);
		return;
	}
	LauncherApp* app = (LauncherApp*)thd->getParam();
	if (!app)
	{
		wxASSERT(false);
		return;
	}

	app->checkVersion();
}

void LauncherApp::gameRun( MG::Ptr manager )
{
	OneThreadHandle* thd = (OneThreadHandle*)manager;
	if (!thd)
	{
		wxASSERT(false);
		return;
	}
	LauncherApp* app = (LauncherApp*)thd->getParam();
	if (!app)
	{
		wxASSERT(false);
		return;
	}
	app->gameStart();
}

void LauncherApp::gameStart()
{
	MG::DllLoader dllLoader;
	MG::IClientMain* clientInterface = NULL;

	GET_MGCLIENT_INTERFACE_PROC proc; 
	std::string dllName;

	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hConsole)
	{
		FreeConsole();
	}
#ifdef _DEBUG
	dllName = "Core\\MGClient_d.dll";
#else
	dllName = "Core\\MGClient.dll";
#endif

	if (dllLoader.load(dllName.c_str(),false)) 
	{ 
		proc = (GET_MGCLIENT_INTERFACE_PROC) dllLoader.getProcAddress("GET_MGCLIENT_INTERFACE"); 
		if (NULL != proc) 
		{
			clientInterface = (MG::IClientMain*)proc(); 
			if (clientInterface==NULL)
			{
				wxMessageBox("Load IClientMain Failed!", "load game dll", wxOK | wxICON_INFORMATION, mMainFrame);
				return;
			}
		}
		else
		{
			wxMessageBox("Don't Find IClientMain Entry!", "load game dll", wxOK | wxICON_INFORMATION, mMainFrame);
			return;
		}
	}
	else
	{
		MessageBoxA(NULL,"Don't Load MGClient DLL!","error",MB_OK);
		return;
	}

	bool isSuccess = clientInterface->initialize();
	if (isSuccess)
	{	
		hide();
		clientInterface->run();
		clientInterface->uninitialize();
		dllLoader.unload();
		hide(false);
		HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		if (hConsole)
		{
			FreeConsole();
		}
	}
	mExit = true;
	hide(false);
}

void LauncherApp::hide( bool isHide /*= true*/ )
{
	if (isHide)
	{
		mMainFrame->Hide();
	}
	else
	{
		mMainFrame->Show();
	}
	
}

void LauncherApp::OnIdle( wxIdleEvent &event )
{
	if (mExit)
	{
		Exit();
	}
}
//------------------------------------------------------------------------------------------------