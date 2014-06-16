
/******************************************************************************/
#include "stdafx.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "FrontServerMain.h"
#include "PlayerCharacterNetPacket.h"
//#include "SWorldManager.h"
#include "ServerManager.h"
#include "SkillObject.h"
#include "SWorldManager.h"
#include "SSkillOwnManager.h"
#include "SClanQuestManager.h"
#include "PlaceObjectData.h"
/******************************************************************************/




namespace MG
{
	//--------------------------------------------------------------------------
	PlayerCharacterNetPacketProcesser::PlayerCharacterNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	PlayerCharacterNetPacketProcesser::~PlayerCharacterNetPacketProcesser()
	{

	}

    //--------------------------------------------------------------------------
    Bool PlayerCharacterNetPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_PLAYER_CHARACTER )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				case PT_PLAYERCHARACTER_C2F_JUMP_REGION:
					onRecvPlayerCharacterJumpRegionFromClient( id , (PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA*)data->data);
					break;
				case PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO:
					onRecvPlayerCharacterJumpTiroRegionFromClient( id , (PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA*)data->data);
					break;
				case PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION:
					onRecvPlayerCharacterJumpOutRegionFromClient( id , (PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA*)data->data);
					break; 
				case PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION:
					onRecvPlayerCharacterJumpLastRegionFromClient( id , (PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA*)data->data);
					break; 
				case PT_PLAYERCHARACTER_C2S_MOVE_POS:
					//onRecvPlayerCharacterMoveClient( id , (PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA*)data->data);
					break;
				default:
					DYNAMIC_ASSERT(0);
					break;
			}

			return true;
		}
		return false;
    }

    //--------------------------------------------------------------------------
    Bool PlayerCharacterNetPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool PlayerCharacterNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_PLAYER_CHARACTER )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
            /*case PT_PLAYERCHARACTER_M2F_ATTR:
                onRecvPlayerCharacterDamage(id, (PT_PLAYERCHARACTER_M2F_ATTR_DATA*)data->data);
                break;*/
			case PT_PLAYERCHARACTER_M2F_JUMP_REGION:
				onRecvPlayerCharacterJumpRegionFromMapServer(id, (PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA*)data->data);
				break;
			}

			return true;
		}
        return false;
    }
    //--------------------------------------------------------------------------
//	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterMoveClient(I32 id , PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data)
//	{
//#if NEW_VERSION_LINHU
//		SPlayerPtr player = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
//
//#else
//		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
//#endif
//
//		//SPlayer* player = SWorldManager::getInstance().getPlayerByClientNetId(id);
//
//		if(!player.isNull())
//		{
//			SClan* clan = player->getMainClan();
//			SPlayerCharacter* playerCharacter = clan->getPlayerCharacterFromList(data->playercharacter_id);
//
//			if(playerCharacter)
//			{
//                // playerCharacter 无法获得地图编号，只有先获得regionType和regionId之后，才可以获得地图编号。
//                //？？？？？？？
//				//I32 id = ServerManager::getInstance().getMapServerNetID(playerCharacter->mMapId);
//				playerCharacter->getMapServerNetId();
//				playerCharacter->getRegionId();
//				playerCharacter->getRegionType();
//				playerCharacter->getInstanceUId();
//				
//				sendNetPacketToActiveMapServerByNetId
//				sendPlayerCharacterMoveToMapServer(id, data);
//			}
//			
//		}
//	}


    //--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterMoveToMapServer(I32 id, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data )
	{

        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER_CHARACTER;
            packet->type    = PT_PLAYERCHARACTER_C2S_MOVE_POS;

            // 复制
            memcpy( packet->data, (Char8*)data, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA_INFO::dataSize );

            // 广播到地图服务器
			



            //ServerManager::getInstance().boardcastNetPacketToAcitveMapServer( dataPtr,
            //    GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA_INFO::dataSize);
        }

        ///////////////////////////////////////////////////////////////////////////

	}
    //--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA*data)
	{
		const PlayerCharacterIdType	playerCharacterId	= data->playerCharacterId;
		const RegionIdType			toRegionId			= data->toRegionId;
		const REGION_OBJ_TYPE		toRegionType		= (REGION_OBJ_TYPE)data->toRegionType;
		const InstanceUIdType		toInstanceUId		= data->toInstanceUId;
		

		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if (playerPtr.isNull())
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		SPlayerCharacter* playerCharacter;// =  playerPtr->getPlayerCharacter(data->playerCharacterId); 
		if (NULL == playerCharacter)
		{
			return;
		}

		//修改角色地图属性
		if(true == ServerManager::getInstance().isMapServerCrash((REGION_OBJ_TYPE)data->toRegionType, data->toRegionId))
		{
			//MapServer 当机
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail_Crash, data->playerCharacterId, data->toRegionId, (REGION_OBJ_TYPE)data->toRegionType, data->toInstanceUId);
			return;
		}

		sendPlayerCharacterJumpToRegionNewVer(playerCharacter, toRegionType, toRegionId, toInstanceUId, data->pointId);
	}

	//--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpTiroRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA*data)
	{
		const PlayerCharacterIdType	playerCharacterId	= data->playerCharacterId;
		const RegionIdType			toRegionId			= data->toRegionId;
		const REGION_OBJ_TYPE		toRegionType		= (REGION_OBJ_TYPE)data->toRegionType;
		const InstanceUIdType		toInstanceUId		= data->toInstanceUId;
		const NetIdType				mapServerNetId		= data->mapServerNetId;

		DYNAMIC_ASSERT(toRegionType == ROT_TIRO && mapServerNetId > 0);
		

		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if (playerPtr.isNull())
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		SPlayerCharacter* playerCharacter;// =  playerPtr->getPlayerCharacter(data->playerCharacterId); 
		if (NULL == playerCharacter)
		{
			return;
		}

		//修改角色地图属性
		if(true == ServerManager::getInstance().isMapServerCrash((REGION_OBJ_TYPE)data->toRegionType, data->toRegionId))
		{
			//MapServer 当机
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail_Crash, data->playerCharacterId, data->toRegionId, (REGION_OBJ_TYPE)data->toRegionType, data->toInstanceUId);
			return;
		}

		sendPlayerCharacterJumpToRegionNewVer(playerCharacter, toRegionType, toRegionId, toInstanceUId, 0, mapServerNetId);
	}

	//--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpOutRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA*data)
	{
		//TODO:是否可以jump
		//sendPlayerCharacterJumpRegionToClient( id, ChatarcterJumpRegionResult_Succeed);

		//修改角色地图属性
		//if(true == ServerManager::getInstance().isMapServerCrash(data->toRegionId))
		//{
		//	//MapServer 当机
		//	//send error msg to client
		//	//sendJumpRegionErrorToClient(id, PlayerCharacter_Jump_server_crash);

		//	SPlayerCharacter* playerCharacter = SWorldManager::getInstance().getGameObjectManager()->getPlayerCharacter(data->playerCharacterId);
		//	if (NULL == playerCharacter)
		//	{
		//		return;
		//	}

		//	sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail_Crash, data->playerCharacterId, (REGION_OBJ_TYPE)data->toRegionType, data->toRegionId, data->toInstanceId);
		//	return;
		//}

		//SWorldManager::getInstance().printWorldObject();

		//表示肯定能成功跳转， 可在这里直接设置clan的Region信息
		//clan->setattRegin();
		const PlayerCharacterIdType playerCharacterId = data->playerCharacterId;

		SPlayerCharacter* playerCharacter;// = SWorldManager::getInstance().getPlayerCharacter(data->accountId, playerCharacterId);
		DYNAMIC_ASSERT(NULL != playerCharacter);

		SRegionObjectBase* curRegion = playerCharacter->getCurrentRegionObject();
		DYNAMIC_ASSERT(NULL != curRegion);

		if (ROT_PLACE != curRegion->getRegionType())
		{
			return;
		}

		PlaceListCsvInfo* placeListCsvInfo = ((PlaceObjectData*)curRegion->getRegionData())->getPlaceListCsvInfo();
		DYNAMIC_ASSERT(NULL != placeListCsvInfo && placeListCsvInfo->mapDistrListId > 0);

		sendPlayerCharacterJumpToRegionNewVer(playerCharacter, ROT_MAP_DISTRIBUTION, placeListCsvInfo->mapDistrListId, 0, placeListCsvInfo->artPointResId);
		//broadcastPlayerCharacterJumpToRegion(data->playerCharacterId, ROT_MAP_DISTRIBUTION,  placeListCsvInfo->mapDistrListId, 0, placeListCsvInfo->artPointResId);
	}

	//--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpLastRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA*data)
	{
		//TODO:是否可以jump
		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if (playerPtr.isNull())
		{
			return;
		}

		SPlayerCharacter* playerCharacter;// = playerPtr->getPlayerCharacter(data->playerCharacterId);
		if (NULL == playerCharacter)
		{
			return;
		}

		const RegionIdType		lastRegionId	= playerCharacter->getLastRegionId();
		const REGION_OBJ_TYPE	lastRegionType	= playerCharacter->getLastRegionType();
		InstanceUIdType	lastInstanceUId			= playerCharacter->getLastInstanceUId();

		if (lastRegionType == ROT_UNKNOWN || lastRegionId <= 0)
		{
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail, data->playerCharacterId, lastRegionId, lastRegionType, lastInstanceUId);
			return;
		}

		//修改角色地图属性
		if(true == ServerManager::getInstance().isMapServerCrash(playerCharacter->getLastRegionType(), lastRegionId))
		{
			//MapServer 当机
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail_Crash, data->playerCharacterId, lastRegionId, lastRegionType, lastInstanceUId);
			return;
		}


		if (playerCharacter->getRegionId()		== lastRegionId		&& 
			playerCharacter->getRegionType()	== lastRegionType	&& 
			playerCharacter->getInstanceUId()	== lastInstanceUId)
		{
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Fail, data->playerCharacterId, lastRegionId, lastRegionType, lastInstanceUId);
			return;
		}

		if (lastRegionType == ROT_PVE || lastRegionType == ROT_TIRO)
		{
			lastInstanceUId = 0;
		}

		sendPlayerCharacterJumpToRegionNewVer(playerCharacter, lastRegionType, lastRegionId, lastInstanceUId);
		//broadcastPlayerCharacterJumpToRegion(data->playerCharacterId, lastRegionType, lastRegionId, lastInstanceUId);
	}

	//--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegionFromMapServer(I32 id, PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA* data)
	{
		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(data->clientNetIdInFront);
		if (playerPtr.isNull())
		{
			// 可能客户端已经退出或断开连接
			// 以后再考虑原因
			//DYNAMIC_ASSERT(false);
			return;
		}

		const PlayerCharacterIdType	playerCharacterId	= data->playerCharacterId;
		const RegionIdType			regionId			= data->toRegionId;
		const REGION_OBJ_TYPE		regionType			= (REGION_OBJ_TYPE)data->toRegionType;
		const InstanceUIdType		instanceUId			= data->toInstanceId;

		SPlayerCharacter* playerCharacter;// =  playerPtr->getPlayerCharacter(playerCharacterId); 
		if (NULL == playerCharacter)
		{
			return;
		}

		if (ChatarcterJumpRegionResult_Succeed != data->jumpResult)
		{
			//跳转失败
			//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), data->jumpResult, playerCharacterId, regionId, regionType, instanceUId);
			//send error

			return;
		}

		playerCharacter->setRegion(regionType, regionId, instanceUId);
		playerCharacter->setMapServerNetId(id);
		//sendPlayerCharacterJumpRegionToClient(playerCharacter->getBelongPlayer()->getClientNetID(), ChatarcterJumpRegionResult_Succeed, data->playerCharacterId, regionId, regionType, instanceUId);

		//SWorldManager::getInstance().printWorldObject();
		//任务判断
        SClanQuestManager* questManager;// = playerPtr->getQuestManager();
		DYNAMIC_ASSERT(questManager);
		questManager->notifyLeaveMap();

		//暂时加在这。等有时间重构的时候整理
		//徐开超
		//playerCharacter->sendDataInfoOnJoinGame();
	}

    //-------------------------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterJumpRegionByMapServerNetIdNewVer(SPlayerCharacter* playerCharacter, NetIdType mapServerNetId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId, Int pointId)
	{
		//3. 开始跳地图
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_F2M_JUMP_REGION;

			// 转换逻辑包
			PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA* sendData = (PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->playerCharacterId = playerCharacter->getID();
				sendData->toRegionId        = regionId;
				sendData->toRegionType      = regionType;
				sendData->toInstanceId		= instanceUId;
				sendData->pointId			= pointId;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2M_JUMP_REGION_INFO::dataSize;
				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					dataSize,mapServerNetId);
			}
		}
	}

    //-------------------------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterJumpToRegionNewVer(SPlayerCharacter* playerCharacter, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId, Int pointId, NetIdType mapServerNetId)
	{
		//1. 从上次地图中删除武将指针
		//sendPlayerCharacterJumpToEmptyRegionNewVer(playerCharacter->getBelongPlayer()->getAccountID(), playerCharacter->getID(), playerCharacter->getMapServerNetId());

		//2. 根据regionType 确认跳地图目的地
		if (mapServerNetId == 0)
		{
			mapServerNetId = SWorldManager::getInstance().getMapServerNetIdByRegion(regionType, regionId);
		}

		sendPlayerCharacterJumpRegionByMapServerNetIdNewVer(playerCharacter, mapServerNetId, regionType, regionId, instanceUId, pointId);
	}

    //-------------------------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterJumpToEmptyRegionNewVer(AccountIdType accountId, PlayerCharacterIdType playerCharacterId, NetIdType mapServerNetId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION;

			// 转换逻辑包
			PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA* sendData = (PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId			= accountId;
				sendData->playerCharacterId = playerCharacterId;

				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_INFO::dataSize, mapServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::broadcastPlayerCharacterJumpToCampaignRegion(PlayerCharacterIdType playerCharacterId, PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA* data)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION;

			// 转换逻辑包
			PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA* sendData = (PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->playerCharacterId	 		= playerCharacterId;
				sendData->toRegionId       	 		= data->toRegionId;
				sendData->toRegionType     	 		= data->toRegionType;
				sendData->toInstanceId				= data->toInstanceId;
				sendData->jumpType					= data->jumpType;
				sendData->jumpIndex					= data->jumpIndex;
				sendData->isBattleLeader			= data->isBattleLeader;
				sendData->prepareTimeSecond			= data->prepareTimeSecond;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_INFO::dataSize;

				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByRegionId( dataPtr, 
					dataSize, (REGION_OBJ_TYPE)data->toRegionType, data->toRegionId);
			}
		}
	}

    //--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterJumpRegionToClient( I32 netId, ChatarcterJumpRegionResult result, PlayerCharacterIdType playerCharacterId, RegionIdType regionId, REGION_OBJ_TYPE regionType, InstanceUIdType instanceUId)
	{
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER_CHARACTER;
            packet->type    = PT_PLAYERCHARACTER_F2C_JUMP_REGION;

            // 转换逻辑包
            PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* sendData = (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
		        sendData->jumpResult		= result;
				sendData->playerCharacterId = playerCharacterId;
				sendData->regionId			= regionId;
				sendData->regionType		= regionType;
				sendData->instanceUId		= instanceUId;

                // 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2C_JUMP_REGION_INFO::dataSize,
					netId );
            }
        }
	}
    
	//-------------------------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterrSkillInfoToMapServer(I32 mapserverNetid, IdType characterId, SSkillOwnManager* skillOwnManager )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;

		// 转换成标准包格式
		GameNetPacketData* packet       = NULL;

		// 转换逻辑包
		PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;


		// 遍历技能队列
		IdType skillId = 0;
		for(UInt i = 0; i < skillOwnManager->getOwnSkillNum(); ++i)
		{

			// 获得技能对象
			skillId = skillOwnManager->getOwnerSkillByIndex(i);
			if(skillId == 0)
			{
				continue;
			}

			//-------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个技能数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA_INFO::elemetSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,sendDataSize, mapserverNetid);
					dataPtr.setNull();
				}
			}

			//-------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// 获得一个发送【客户端】缓存
				FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				// 转换成标准包格式
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				// 设置标签
				packet->channel = GNPC_PLAYER_CHARACTER;
				packet->type    = PT_PLAYERCHARACTER_F2M_SKILL_INFO;

				// 转换逻辑包
				sendData = (PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA*)(packet->data);
				sendData->playercharacterId = characterId;
				// 清空
				sendData->skillNum = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//-------------------------------------------------------------------------------------------

			// 增加技能记录
			SkillNetData* skillNetData = &(sendData->skillList[sendData->skillNum]);
			skillNetData->skillId      = skillId;

			// 递增参数
			sendDataSize += PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA_INFO::elemetSize;
			++sendData->skillNum;
		}

		//-------------------------------------------------------------------------------------------
		// 如果有剩余则发送
		if ( dataPtr.isNull() == false )
		{
			FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,sendDataSize, mapserverNetid);
			dataPtr.setNull();
		}
		
	}

    //--------------------------------------------------------------------------
    void PlayerCharacterNetPacketProcesser::sendAllPlayerCharacterSkillInfoInClanToClient( I32 id, SClanPtr& clanPtr )
    {
		SPlayerCharacterPtr playerCharacter;
		clanPtr->getMainPlayerCharacter(playerCharacter);
		//playerCharacter.sendPlayerCharacterSkillInfoToClient();
  //      std::map<U64, SPlayerCharacter*>::iterator iter = mPlayerCharacterList.begin();
  //      for ( ;iter != mPlayerCharacterList.end();iter++ )
  //      {
  //          iter->second->sendPlayerCharacterSkillInfoToClient();
  //      }


    }

    //--------------------------------------------------------------------------
	void PlayerCharacterNetPacketProcesser::sendPlayerCharacterSkillInfoToClient(I32 id, IdType characterId, SSkillOwnManager* skillOwnManager)
	{		
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        
        // 转换成标准包格式
        GameNetPacketData* packet       = NULL;

        // 转换逻辑包
        PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA* sendData = NULL;

        // 当前发送数据头大小
        I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA_INFO::headSize;
        // 当前发送数据大小
        I32 sendDataSize        = sendDataHeadSize;
        // 准备发送数据大小
        I32 prepareSendDataSize = sendDataHeadSize;

        // 遍历技能队列
        IdType skillId = 0;
        for(UInt i = 0; i < skillOwnManager->getOwnSkillNum(); ++i)
        {

			// 获得技能对象
			skillId = skillOwnManager->getOwnerSkillByIndex(i);
			if(skillId == 0)
			{
				continue;
			}


			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个技能数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA_INFO::elemetSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					//dataPtr->send( sendDataSize, id );
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
					
					dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// 获得一个发送【客户端】缓存
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				// 转换成标准包格式
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				// 设置标签
				packet->channel = GNPC_PLAYER_CHARACTER;
				packet->type    = PT_PLAYERCHARACTER_F2C_SKILL_INFO;

				// 转换逻辑包
				sendData = (PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA*)(packet->data);
				sendData->playercharacterId = characterId;
				// 清空
				sendData->skillNum = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
            
            // 增加技能记录
            SkillNetData* skillNetData = &(sendData->skillList[sendData->skillNum]);
            skillNetData->skillId      = skillId;

            // 递增参数
            sendDataSize += PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA_INFO::elemetSize;
            ++sendData->skillNum;
        }

		//--------------------------------------------------------------------------
        // 如果有剩余则发送
        if ( dataPtr.isNull() == false )
        {
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
			dataPtr.setNull();
        }
	}

}