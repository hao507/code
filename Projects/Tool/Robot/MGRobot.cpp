
// MGRobot.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MGRobot.h"
#include "MGRobotDlg.h"
#include "MainFrm.h"
//#include "ClientManager.h"
#include "ServerConfig.h"
#include "ClientNetApplyManager.h"
#include "mmsystem.h"
#include "CRegionManager.h"
//#include "CCampaignManager.h"
#include "InstanceListCsv.h"
#include "StlAlloc.h"
#include "CharacterResourceConfig.h"
#include "ChannelInfo.h"
#include "ThreadTaskManager.h"
#include "RobotTaskThread.h"

#include "ClientNetApplyManager.h"


#include "CharacterResourceConfig.h"
#include "CharacterList.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "CharacterLvlTemplate.h"
#include "AttributeAppend.h"
#include "AttributePara.h"
#include "AttributeList.h"
#include "CDTemplate.h"
//#include "AttributeRelation.h"
#include "ItemShopTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemRandomTemplate.h"
#include "ArtIconResCsv.h"
#include "NpcFuctionInfo.h"
#include "ItemSiteTemplate.h"



#include "CharacterSkillTempLate.h"
#include "ChannelInfo.h"
#include "CRegionManager.h"
#include "NetPacketPackManager.h"
#include "Dialog.h"

#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "PassivenessSkillTemplate.h"
#include "SkillInfoList.h"
#include "SkillLearn.h"
#include "SelfAreaSkillTemplate.h"
#include "SingleEmitterSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "ParabolaAreaSkillTemplate.h"
#include "GoUpAndDownSkillTemplate.h"

#include "BigMapResCsv.h"
#include "InstanceListCsv.h"
#include "ArtDecalResTemplate.h"
#include "GameRadarConfig.h"
#include "DialogueVassal.h"

#include "BaseAITemplate.h"
#include "BaseAIGroupTemplate.h"
#include "FightAITemplate.h"
#include "FightAiGroupTemplate.h"

#include "CharacterVisionEvent.h"
#include "CharacterVisionEventList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//using namespace MG;
//-----------------------------------------------------------------------
// CMGRobotApp
BEGIN_MESSAGE_MAP(CMGRobotApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------
// CMGRobotApp ����
CMGRobotApp::CMGRobotApp()
{
	// TODO: �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}
//-----------------------------------------------------------------------
// Ψһ��һ�� CMGRobotApp ����
CMGRobotApp theApp;
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
//����
//-----------------------------------------------------------------------

struct TestPlayer
{
	
    int  id;
	std::wstring name;
	int old;
	std::wstring fame;
	std::wstring game;

};

void testAllocator()
{


	 //std::map<int, TestPlayer*, less<int>,  MG::StlAllocator<TestPlayer*>> playerList;
	 std::map<int, TestPlayer*> playerList;
	 for (int i = 0;i<50000;i++)
	 {
		 TestPlayer* P = new TestPlayer();
		 P->id = i+1;
		 P->name = L"name1";
		 P->old = 20;
		 P->fame = L"SSSSSSSSSSSSSSSAAAAAAAAAAAAAAAAAA";
		 P->game = L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

		/* TestPlayer* P2 = new TestPlayer();
		 P2->id = 2;
		 P2->name = L"name2";
		 P2->old = 20;

		TestPlayer* P3 = new TestPlayer();
			P3->id = 3;
		 P3->name = L"name3";
		 P3->old = 20;

		 TestPlayer* P4 = new TestPlayer();
		 P4->id = 4;
		 P4->name = L"name4";
		 P4->old = 20;*/


		 playerList[P->id] = P;
		
	 }
	 int stop = true;
}



// CMGRobotApp ��ʼ��
BOOL CMGRobotApp::InitInstance()
{
	
	
	//testAllocator();
	mIsThreadActive = 0;
	mIsUpdate = false;
	if (!loadGameRes())
	{
		return FALSE;
	}
	
	AfxInitRichEdit();

	MG::U32 processId = GetCurrentProcessId();
	std::string path = "log";
	//path += processId;
	MG::LogSystem::getInstance().setSysLogPath(path.c_str());
	MG::LogSystem::getInstance().setGameLogicLogPath(path.c_str());
	MG::LogSystem::getInstance().setPartName("Robot");
	MG::LogSystem::getInstance().setEnableConsole(true);
	MG::LogSystem::getInstance().setSaveToFile(true);

	MG::ThreadMonitor::getInstance().initialize();
	MG::ThreadMonitor::getInstance().setPrintLog(true);
	MG::ThreadMonitor::getInstance().setCalcFrequency(5);
	MG::ThreadMonitor::getInstance().start();

	if (!MG::ClientNetApplyManager::getInstance().initialize())
	{
		MG::LogSystem::getInstance().log(MG::out_error,"failed to init net");
		return FALSE;
	}

	if (!MG::CRegionManager::getInstance().initialize())
	{
		MG::LogSystem::getInstance().log(MG::out_error,"failed to init CRegionManager");
		return FALSE;
	}
	//MG::CCampaignManager::getInstance().init();
	mThreadHandle.create(CMGRobotApp::gameRun,&theApp,"CMGRobotApp::mThreadHandle");
	mIsThreadActive = 1;

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	MG::LogSystem::getInstance().setLogLevel(MG::out_max);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//AfxEnableControlContainer();
	
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
	{
		return FALSE;
	}
	m_pMainWnd = pFrame;
	// ���������ش�������Դ�Ŀ��
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
//-----------------------------------------------------------------------
void CMGRobotApp::gameRun( MG::Ptr ptr )
{

	MG::OneThreadHandle* thd = (MG::OneThreadHandle*)ptr;
	if (thd)
	{
		CMGRobotApp* app = (CMGRobotApp*)thd->getParam();
		app->mIsUpdate = true;
		if (app)
		{
			while(app->mIsThreadActive == 1 && thd->isRun())
			{

				
#ifdef ONE_THREAD
# else
				MG::ClientNetApplyManager::getInstance().update();
#endif
				//Sleep(1);
			}
			
		}
		app->mIsUpdate = false;
	}
	
	
}
//-----------------------------------------------------------------------
bool CMGRobotApp::loadGameRes()
{
	//if (CServerConfig::loadServerInfo() == false)
	//	return false;
	////�����б�
	//if ( MG::InstanceListCsv::getInstance().load(L"Config\\World\\Instance\\InstanceList.csv") == false )
	//	return false;
	//if (MG::CharacterResourceConfig::getInstance().load(L"Config\\World\\CharacterCreate.csv") ==false)
	//	return false;
	//if (MG::ChannelInfos::getInstance().loadFile(L"Config\\World\\ChatChannelList.csv") ==false)
	//	return false;


	if ( MG::ShortRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType003List.csv") == false )
	{
		MG::MsgBox::show("����SkillType003List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::LongRangeGeneralAttackSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType004List.csv") == false )
	{
		MG::MsgBox::show("����SkillType004List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::SingleTargetSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType005List.csv") == false )
	{
		MG::MsgBox::show("����SkillType005List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::PassivenessSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType002List.csv") == false )
	{
		MG::MsgBox::show("����SkillType002List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::SingleEmitterSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType006List.csv") == false )
	{
		MG::MsgBox::show("����SkillType006List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::SelfAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType007List.csv") == false )
	{
		MG::MsgBox::show("����SkillType007List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::TargetPosAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType008List.csv") == false )
	{
		MG::MsgBox::show("����SkillType008List.csvʧ��","Error");
		return FALSE;
	}
	if ( MG::ParabolaAreaSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType014List.csv") == false )
	{
		MG::MsgBox::show("����SkillType014List.csvʧ��","Error");
		return false;
	}
	if ( MG::GoUpAndDownSkillTemplate::getInstance().load(L"Config\\Game\\Skill\\SkillType013List.csv") == false )
	{
		MG::MsgBox::show("����SkillType013List.csvʧ��","Error");
		return false;
	}
	if ( MG::SkillInfoList::getInstance().load(L"Config\\Game\\Skill\\SkillList.csv") == false )
	{
		MG::MsgBox::show("����SkillList.csvʧ��","Error");
		return false;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (MG::ChannelInfos::getInstance().loadFile(L"Config\\Game\\Setting\\ChatChannelList.csv")==false)
	{
		MG::MsgBox::show("����ChatChannel.csvʧ��","Error");
		return false;
	}

	if ( MG::CharacterLvlTemplate::getInstance().load(L"Config\\Game\\Setting\\Level.csv") == false )
	{
		MG::MsgBox::show("����Level.csvʧ��","Error");
		return false;
	}

	/*if ( MG::AttributeAppend::getInstance().load(L"Config\\Game\\Setting\\AbilityAppend.csv") == false )
	{
		MG::MsgBox::show("����AbilityAppend.csvʧ��","Error");
		return false;
	}

	if ( MG::AttributeList::getInstance().load(L"Config\\Game\\Setting\\Ability.csv") == false )
	{
		MG::MsgBox::show("����Ability.csvʧ��","Error");
		return false;
	}

	if ( MG::AttributePara::getInstance().load(L"Config\\Game\\Setting\\FormulaParameter.csv") == false )
	{
		MG::MsgBox::show("����FormulaParameter.csvʧ��","Error");
		return false;
	}*/

	if ( MG::CDTemplate::getInstance().load(L"Config\\Game\\Setting\\Timepiece.csv") == false )
	{
		MG::MsgBox::show("����Timepiece.csvʧ��","Error");
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( MG::CharacterResourceConfig::getInstance().load(L"Config\\Game\\Character\\CharacterCreate.csv") == false)
	{
		MG::MsgBox::show("����CharacterCreate.csvʧ��","Error");
		return false;
	}
	if ( MG::CharacterArmyList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterArmyList.csv") == false )
	{
		MG::MsgBox::show("����CharacterArmyList.csvʧ��","Error");
		return false;
	}
	if ( MG::CharacterBuildList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterBuildList.csv") == false )
	{
		MG::MsgBox::show("����CharacterBuildList.csvʧ��","Error");
		return false;
	}
	if ( MG::CharacterGenrealList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterGeneralList.csv") == false )
	{
		MG::MsgBox::show("����CharacterGeneralList.csvʧ��","Error");
		return false;
	}
	if ( MG::CharacterNpcList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterNpcList.csv") == false )
	{
		MG::MsgBox::show("����CharacterNpcList.csvʧ��","Error");
		return false;
	}
	if ( MG::CharacterObjectList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterObjectList.csv") == false )
	{
		MG::MsgBox::show("����CharacterObjectList.csvʧ��","Error");
		return false;
	}
	/*if ( MG::CharacterMonsterList::getInstance().loadFile(L"Config\\Game\\Character\\CharacterMonsterList.csv") == false )
	{
		MG::MsgBox::show("����CharacterMonsterList.csvʧ��","Error");
		return false;
	}*/
	if (MG::DialogueVassal::getInstance().load(L"Config\\Game\\Character\\DialogueVassal.csv") == false)
	{
		MG::MsgBox::show("����DialogueVassal.csvʧ��","Error");
		return false;
	}

	if ( MG::CharacterTemplate::getInstance().loadFile(L"Config\\Game\\Character\\CharacterList.csv") == false )
	{
		MG::MsgBox::show("����CharacterList.csvʧ��","Error");
		return false;
	}

	if (MG::NpcFunctionInfos::getInstance().load(L"Config\\Game\\Character\\DialogueFunctionList.csv") == false)
	{
		MG::MsgBox::show("����DialogueFunctionList.csvʧ��","Error");
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------
void CMGRobotApp::unLoadGameRes()
{
	CServerConfig::freeServerInfo();
}



int CMGRobotApp::ExitInstance()
{
	mIsThreadActive = 0;
	while (!mIsUpdate)
	{
		Sleep(5);
	}
	mThreadHandle.destory();
	Sleep(5);
	MG::ClientNetApplyManager::getInstance().unInitialize();
	unLoadGameRes();
	return CWinApp::ExitInstance();
}