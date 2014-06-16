/******************************************************************************/
#include "stdafx.h"
#include "ClanDBProcessor.h"
#include "SClan.h"
#include "ItemDBProcessor.h"
#include "QuestDBProcessor.h"
#include "PlayerItem.h"
#include "ClanQuestObject.h"
#include "ClanDBSystem.h"
#include "FrontServerMain.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------------
    ClanDBProcessor::ClanDBProcessor()
    {
    }

    //-----------------------------------------------------------------------------
    ClanDBProcessor::~ClanDBProcessor()
    {
    }

    //-----------------------------------------------------------------------------
    void ClanDBProcessor::loadAndCreateAllClanInPlayer( SPlayerPtr& playerPtr )
    {
        // ֻ�����������,��Ҫǣ����������ж�
		std::vector<ClanData>					clanDataList;
		std::vector<dbDoingClanQuestObject>		doingQuestData;
		std::vector<FinishedClanQuestObject>	finishedQuestData; 
		std::vector<ItemRecord>					recordList; 

        // ��ȡ����һ��
		ClanDBSystem::getClanDataBase(
			FrontServerMain::getInstance().getDBDriver()
			,playerPtr->getAccountID()
			, &clanDataList
			, &doingQuestData
			, &finishedQuestData
			, &recordList
			);

        // ��������
        SClanPtr clanPtr;

		std::vector<ClanData>::iterator beginIter = clanDataList.begin();
		std::vector<ClanData>::iterator endIter = clanDataList.end();
		while (beginIter != endIter)
		{
			// ����һ������
			playerPtr->addClan( clanPtr, *beginIter );

			//��������������Ϣ��
			QuestDBProcessor::getInstance().loadQuestInClan( clanPtr, doingQuestData, finishedQuestData );
			//�������������Ϣ��
			ItemDBProcessor::getInstance().loadItemRecordInClan( clanPtr, recordList );

			++beginIter;
		}  
    }
	//-----------------------------------------------------------------------------
	Bool ClanDBProcessor::updateClanDataInfo( const ClanData* _clandata )
	{
		ClanDBSystem::updateClanDataBase(
			FrontServerMain::getInstance().getDBDriver(),
			_clandata
			);

		return true;
	}
	//-----------------------------------------------------------------------------
	MG::Bool ClanDBProcessor::insertClanDataInfo( const ClanData* _clandata )
	{
		ClanDBSystem::insertClanDataBase(
			FrontServerMain::getInstance().getDBDriver(),
			_clandata
			);

		return true;
	}
}