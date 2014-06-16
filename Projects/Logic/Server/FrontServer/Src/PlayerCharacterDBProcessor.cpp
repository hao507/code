/******************************************************************************/
#include "stdafx.h"
#include "PlayerCharacterDBProcessor.h"
#include "SClan.h"
#include "ItemDBProcessor.h"
#include "PlayerItem.h"
#include "FrontServerMain.h"
#include "PlayerCharacterDBSystem.h"
#include "ItemDBProcessor.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------------
    PlayerCharacterDBProcessor::PlayerCharacterDBProcessor()
    {
    }

    //-----------------------------------------------------------------------------
    PlayerCharacterDBProcessor::~PlayerCharacterDBProcessor()
    {
    }

    //-----------------------------------------------------------------------------
    void PlayerCharacterDBProcessor::loadAndCreateAllPlayerCharacterInPlayer( SPlayerPtr& playerPtr )
    {
		SClanPtr pSClanPtr;
		if ( false == playerPtr->getMainClan(pSClanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "找不到氏族对象");
			//退出登陆
			return;
		}

		std::vector<PlayerCharacterData>* charList; 
		std::vector<ItemRecord>* itemRecordList;
		std::map<IdType, std::map<UInt, BuffData> >* mapPlayerCharBuff;

        // 读取角色表一次
		PlayerCharacterDBSystem::getPlayerCharactersNameMap(
			FrontServerMain::getInstance().getDBDriver()
			, playerPtr->getAccountID()
			, pSClanPtr->getClanID()
			, charList
			, itemRecordList
			, mapPlayerCharBuff
			);

        // 创建角色
        // Loop Clan In Player
        {
			SPlayerCharacterPtr playerCharPtr;

			std::vector<PlayerCharacterData>::iterator beginIter = charList->begin();
			std::vector<PlayerCharacterData>::iterator endIter = charList->end();
			while (beginIter != endIter)
			{
				pSClanPtr->addPlayerCharacter( playerCharPtr, *beginIter );

				//加载角色道具信息。
				ItemDBProcessor::getInstance().loadItemRecordInPlayerCharacter( playerCharPtr, *itemRecordList );

				++endIter;
			}
        }
    }
	//-----------------------------------------------------------------------------
	MG::Bool PlayerCharacterDBProcessor::insertGenrealDataInfo( const PlayerCharacterData* _PlayerCharacterData )
	{
		PlayerCharacterDBSystem::createPlayerCharacter(
			FrontServerMain::getInstance().getDBDriver()
			, _PlayerCharacterData
			, _PlayerCharacterData->charAccountId
			);

		return true;
	}
}
