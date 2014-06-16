
/******************************************************************************/

#include "stdafx.h"
#include "CampaignNetPacketProcesser.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "GameNetPacket.h"
#include "SClan.h"
#include "SWorldManager.h"
#include "CampaignManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	CampaignNetPacketProcesser::CampaignNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	CampaignNetPacketProcesser::~CampaignNetPacketProcesser()
	{

	}

    //--------------------------------------------------------------------------
	Bool CampaignNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			//case PT_CAMPAIGN_M2F_CREATE:
			//	onRecvMapServerCampaignCreate(id, (PT_CAMPAIGN_M2F_CREATE_DATA*)data->data );
			//	break;
			//case PT_CAMPAIGN_SC_LIST:
			//	onRecvMapServerCampaignList(id, (PT_CAMPAIGN_SC_LIST_DATA*)data->data );
				//break;
			//case PT_CAMPAIGN_SC_ENTER:
			//	onRecvMapServerCampaignEnter(id, (PT_CAMPAIGN_SC_ENTER_DATA*)data->data );
			//	break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	Bool CampaignNetPacketProcesser::processCenterServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CAMPAIGN_T2F_MEMBER_LIST:
				onRecvCampaignMemberListFromCenterServer( id , (PT_CAMPAIGN_T2F_MEMBER_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_ENTER_ATTACK:
				onRecvCampaignEnterAttackFromCenterServer( id , (PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_ENTER_DEFENSE:
				onRecvCampaignEnterDefenseFromCenterServer( id , (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_START:
				onRecvCampaignStartFromCenterServer( id , (PT_CAMPAIGN_T2F_START_DATA*)data->data);
				break;
			//case  PT_CAMPAIGN_T2F_CREATE:
			//	onRecvCampaignCreateFromCenterServer( id , (PT_CAMPAIGN_T2F_CREATE_DATA*)data->data);
			//	break;
			case PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL:
				onRecvCampaignChangeCampControlFromCenterServer( id , (PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA*)data->data);
				break;
			//case PT_CAMPAIGN_T2F_ENTER:
			//	onRecvCampaignEnterFromCenterServer( id , (PT_CAMPAIGN_T2F_ENTER_DATA*)data->data);
			//	break;

			//case PT_CAMPAIGN_T2F_ERROR:
				//onRecvCampaignErrorFromCenterServer( id , (PT_CAMPAIGN_T2F_ERROR_DATA*)data->data);
			//	break;
			case PT_CAMPAIGN_T2F_START_JUMP_REGION:
				onRecvCampaignStartJumpRegionFromCenterServer( id , (PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_END:
				onRecvCampaignEndFromCenterServer( id , (PT_CAMPAIGN_T2F_END_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER:
				onRecvCampaignCreateCampByControlerFromCenterServer( id , (PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER:
				onRecvCampaignChangeCampOwnerByControlerFromCenterServer( id , (PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST:
				onRecvCampaignTroopControllerListFromCenterServer( id , (PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN:
				onRecvCampaignLeaveInCampaignFromCenterServer( id , (PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA*)data->data);
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
	Bool CampaignNetPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case  PT_CAMPAIGN_C2F_CREATE:	
				onRecvCampaignCreateFromClient( id , (PT_CAMPAIGN_C2F_CREATE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_ENTER_ATTACK:
				onRecvClientCampaignEnterFromClient( id , (PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_ENTER_DEFENSE:
				onRecvClientCampaignEnterDefenseFromClient( id , (PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_READY_MYSELF:
				onRecvClientCampaignReadyMySelf( id , (PT_CAMPAIGN_C2F_READY_MYSELF_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_LEAVE:
				onRecvClientCampaignLeave( id , (PT_CAMPAIGN_C2F_LEAVE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN:
				onRecvClientCampaignLeaveCampaign( id , (PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_CAMPAIGN_LIST:
				onRecvCampaignListFromClient( id , (PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_START:
				onRecvClientCampaignStart( id , (PT_CAMPAIGN_C2F_START_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL:
				onRecvClientCampaignChangeCampControl( id , (PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST:
				onRecvClientCampaignTroopControllerList( id , (PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_END_MANUAL:
				onRecvClientCampaignEndManual( id , (PT_CAMPAIGN_C2F_END_MANUAL_DATA*)data->data);
				break;
			case PT_CAMPAIGN_C2F_END_SCORE:
				onRecvClientCampaignEndScore( id , (PT_CAMPAIGN_C2F_END_SCORE_DATA*)data->data);
				break;
			default:
				DYNAMIC_ASSERT_LOG(0, "default");
				break;
			}
			

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignCreateFromClient( I32 id, PT_CAMPAIGN_C2F_CREATE_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
        if (player.isNull())
        {
            //
            return;
        }
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		SPlayerCharacter* myCharacter;// = clan->getMainPlayerCharacter();

#if 0	//2012.12�·ݰ汾 �ݲ������ƣ��������޿�������
		SRegionObjectBase* targetRegion = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != targetRegion);
		if (targetRegion->getCampaignId() > 0)
		{
			sendCampaignErrorToClient(player->getClientNetID(), REGION_HAS_CAMPAIGM);
			return;
		}
#endif
        
		//--------------------------------------------------------------------------

		//sendCampaignCreateToCenterServer(data, clan, player);
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_CREATE;

			// ת���߼���
			PT_CAMPAIGN_F2T_CREATE_DATA* sendData = (PT_CAMPAIGN_F2T_CREATE_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId		    		= player->getAccountID();
				sendData->clientNetId				= player->getClientNetID();
				sendData->creatorClanId	    		= data->creatorClanId;
				//sendData->creatorPlayerCharacterId	= clan->getMainPlayerCharacter()->getID();
				sendData->charArtIcon				= myCharacter->getData()->charArtIcon;
				sendData->targetRegionId			= data->targetRegionId;
				sendData->targetRegionType			= data->targetRegionType;
				WStrnCpyS(sendData->creatorClanName, clan->getData()->clanName.c_str(), MAX_CLAN_NAME);
				//WStrnCpyS(sendData->creatorPlayerCharacterName, clan->getMainPlayerCharacter()->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->campaignName, data->campaignName, MAX_CAMPAIGN_NAME);

				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_CREATE_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignChangeCampControl( I32 id, PT_CAMPAIGN_C2F_CHANGE_CAMP_CONTROL_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}
		
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		//--------------------------------------------------------------------------

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL;

			// ת���߼���
			PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA* sendData = (PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->campaignId				= data->campaignId;
				sendData->ownerAccountId			= data->ownerAccountId;
				sendData->campId					= data->campId;
				sendData->targetControlerAccountId  = data->targetControlerAccountId;

				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignTroopControllerList( I32 id, PT_CAMPAIGN_C2F_TROOP_CONTROLLER_LIST_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}

		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		//--------------------------------------------------------------------------

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST;

			// ת���߼���
			PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA* sendData = (PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->myAccountId	= data->myAccountId;
				sendData->campaignId	= data->campaignId;
				sendData->myClanId		= clan->getClanID();
				sendData->campId		= data->campId;

				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignEndManual( I32 id, PT_CAMPAIGN_C2F_END_MANUAL_DATA* data )
	{
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_F2T_END_MANUAL;

		// ת���߼���
		PT_CAMPAIGN_F2T_END_MANUAL_DATA* sendData = (PT_CAMPAIGN_F2T_END_MANUAL_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->campaignId = data->campaignId;

		// ��������
		ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
			GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_END_MANUAL_INFO::dataSize );
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignEndScore( I32 id, PT_CAMPAIGN_C2F_END_SCORE_DATA* data )
	{
		//��ý���
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		DYNAMIC_ASSERT( !player.isNull() );

		SClan* pSClan;// = player->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SPlayerCharacter* pSPlayerCharacter;// = pSClan->getPlayerCharacterFromList(data->playerCharacterId);
		DYNAMIC_ASSERT(pSPlayerCharacter);

		SItemManager* pItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pItemManager);

		pItemManager->handlRewardItemMapServer(pSPlayerCharacter, data->itemGroupId);

		//CenterServer ���� ���Ϊ�뿪
		//Ч����ͬ
		sendCampaignDisconnectToCenterServer(player);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignChangeCampControlFromCenterServer(I32 id , PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA* data)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL;

			// ת���߼���
			PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA* sendData = (PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->targetRegionId			= data->targetRegionId;
				sendData->targetInstanceUId			= data->targetInstanceUId;
				sendData->ownerAccountId			= data->ownerAccountId;
				sendData->campId					= data->campId;
				sendData->targetControlerAccountId	= data->targetControlerAccountId;

				// ��������
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_INFO::dataSize,
					region->getMapServerNetId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignLeave( I32 id, PT_CAMPAIGN_C2F_LEAVE_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		//--------------------------------------------------------------------------

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_LEAVE;

			// ת���߼���
			PT_CAMPAIGN_F2T_LEAVE_DATA* sendData = (PT_CAMPAIGN_F2T_LEAVE_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->accountId     = player->getAccountID();
				//sendData->regionId      = data->regionId;
				sendData->campaignId    = data->campaignId;
				sendData->clanId        = data->clanId;

				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_LEAVE_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignLeaveCampaign( I32 id, PT_CAMPAIGN_C2F_LEAVE_IN_CAMPAIGN_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		//--------------------------------------------------------------------------

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
		FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN;

			// ת���߼���
			PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA* sendData = (PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->accountId     = player->getAccountID();
				sendData->clientNetId	= player->getClientNetID();
				sendData->campaignId    = data->campaignId;
				sendData->clanId        = data->clanId;

				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignMemberListFromCenterServer(I32 id , PT_CAMPAIGN_T2F_MEMBER_LIST_DATA* data)
	{
		DYNAMIC_ASSERT(data->addMemberNum >= 0);
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			return;
		}

		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2C_MEMBER_LIST;

			PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* sendData = (PT_CAMPAIGN_F2C_MEMBER_LIST_DATA*)(packet->data);
			sendData->addMemberNum = 0;

			// ��ǰ��������ͷ��С
			I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO::headSize;
			// ��ǰ�������ݴ�С
			I32 sendDataSize        = sendDataHeadSize;
			// ׼���������ݴ�С
			I32 prepareSendDataSize = sendDataHeadSize;

			sendData->frontServerNetId	= data->frontServerNetId;
			sendData->campaignId		= data->campaignId;
			sendData->force				= data->force;
			sendData->addMemberNum		= data->addMemberNum;

			memcpy(sendData->addMemberInfo, data->addMemberInfo, GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO::dataSize(sendData));
			// TODO: ����AccountId����ȷ ��ҪС��ȷ�� king		
			
			for (Int i=0; i<data->addMemberNum; ++i)
			{
				NetCampaignMemberInfo* tempInfo = &(sendData->addMemberInfo[i]);

				
				SPlayerCharacter* playerCharacter;// =  SWorldManager::getInstance().getPlayerCharacter(tempInfo->accountId, tempInfo->playerCharacterId);
				if (NULL == playerCharacter)
				{
					continue;
				}

				WStrnCpyS(tempInfo->playerCharacterName, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);

				tempInfo->level			= playerCharacter->getLevel();
				tempInfo->hp			= playerCharacter->getHp();
				tempInfo->mp			= playerCharacter->getMp();
			}

			SPlayerPtr myPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByAccountId(data->accountId);
			if ( myPlayerPtr.isNull() ) return;
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_MEMBER_LIST_DATA_INFO::dataSize(sendData), 
				myPlayerPtr->getClientNetID());
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignStart( I32 id, PT_CAMPAIGN_C2F_START_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		///////////////////////////////////////////////////////////////////////////

		sendCampaignStartToCenterServer(data, player);

		///////////////////////////////////////////////////////////////////////////

	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignCreateToCenterServer(PT_CAMPAIGN_C2F_CREATE_DATA* data,SClan* clan, SPlayer* player)
	{
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignStartToCenterServer(PT_CAMPAIGN_C2F_START_DATA* data, SPlayerPtr player)
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_START;

			// ת���߼���
			PT_CAMPAIGN_F2T_START_DATA* sendData = (PT_CAMPAIGN_F2T_START_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->clientNetId	= player->getClientNetID();
				sendData->campaignId	= data->campaignId;
				sendData->starterClanId	= data->starterClanId;
				sendData->accountId		= player->getAccountID();
				
				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_START_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignStartToMapServer(NetIdType mapServerNetId, PT_CAMPAIGN_T2F_START_DATA* data)
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2M_START;

			// ת���߼���
			PT_CAMPAIGN_F2M_START_DATA* sendData = (PT_CAMPAIGN_F2M_START_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId			= data->accountId;
				sendData->targetRegionId	= data->targetRegionId;
				sendData->campaignId		= data->campaignId;

				// ��������
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_START_INFO::dataSize,
					mapServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignEnterFromClient( I32 id, PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA* data )
	{
		SPlayerPtr myPlayer;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
        if (myPlayer.isNull())
        {
            //
            return;
        }

		SClan* clan;// = myPlayer->getMainClan();

		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		SPlayerCharacter* myPlayerCharacter;// = clan->getMainPlayerCharacter();
		if (NULL == myPlayerCharacter)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		//sendCampaignEnterToCenterServer(id, data, player);
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_F2T_ENTER_ATTACK;

		// ת���߼���
		PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA* sendData = (PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->clientNetId			= myPlayer->getClientNetID();
		sendData->accountId				= myPlayer->getAccountID();
		sendData->campaignId			= data->campaignId;
		sendData->myClanId				= data->myClanId;
		sendData->myPlayerCharacterId	= myPlayerCharacter->getID();
		sendData->charArtIcon			= myPlayerCharacter->getData()->charArtIcon;
		//WStrnCpyS(sendData->myClanName, myPlayer->getMainClan()->getClanHomeLandName().c_str(), MAX_CLAN_NAME);
		WStrnCpyS(sendData->myPlayerCharacterName, myPlayerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
		// ��������
		ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
			GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_ENTER_ATTACK_INFO::dataSize );
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignEnterDefenseFromClient( I32 id, PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA* data )
	{
		SPlayerPtr myPlayer;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (myPlayer.isNull())
		{
			//
			return;
		}

		SClan* clan;// = myPlayer->getMainClan();

		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		SPlayerCharacter* myPlayerCharacter;// = clan->getMainPlayerCharacter();
		if (NULL == myPlayerCharacter)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_ENTER_DEFENSE;

			// ת���߼���
			PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->clientNetId			= myPlayer->getClientNetID();
				sendData->accountId				= myPlayer->getAccountID();
				sendData->campaignId			= data->campaignId;
				sendData->myClanId				= data->myClanId;
				sendData->myPlayerCharacterId	= myPlayerCharacter->getID();
				sendData->charArtIcon			= myPlayerCharacter->getData()->charArtIcon;
				//WStrnCpyS(sendData->myClanName, myPlayer->getMainClan()->getClanHomeLandName().c_str(), MAX_CLAN_NAME);
				WStrnCpyS(sendData->myPlayerCharacterName, myPlayerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				
				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_ENTER_DEFENSE_INFO::dataSize );
			}
		}
	}

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignEnterToCenterServer(NetIdType clientNetId, PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA* data, SPlayer* myPlayer)
	{
		
	}
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignDisconnectToCenterServer(SPlayerPtr player)
	{
		DYNAMIC_ASSERT(!player.isNull());
		const REGION_OBJ_TYPE regionType = player->getCurrentRegionType();
		const RegionIdType regionId = player->getCurrentRegionId();
		if (regionId <= 0)
		{
			return;
		}
		SRegionObjectBase* regionObj = SWorldManager::getInstance().getRegionObject(regionType, regionId);
		DYNAMIC_ASSERT(NULL != regionObj);



		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
			
		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_F2T_DISCONNECT;

		// ת���߼���
		PT_CAMPAIGN_F2T_DISCONNECT_DATA* sendData = (PT_CAMPAIGN_F2T_DISCONNECT_DATA*)(packet->data);
		if ( sendData )
		{
			//����߼���
			//sendData->clanId		= player->getMainClan()->getClanID();
			//sendData->campaignId	= regionObj->getCampaignId();

			// ��������
			ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_DISCONNECT_INFO::dataSize );
		}
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvClientCampaignReadyMySelf( I32 id, PT_CAMPAIGN_C2F_READY_MYSELF_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
        if (player.isNull())
        {
            //
            return;
        }
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

        ///////////////////////////////////////////////////////////////////////////

        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_F2T_READY_MYSELF;

            // ת���߼���
            PT_CAMPAIGN_F2T_READY_MYSELF_DATA* sendData = (PT_CAMPAIGN_F2T_READY_MYSELF_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->clientNetId	        = player->getClientNetID();
                sendData->campaignId	        = data->campaignId;
                sendData->myClanId				= data->myClanId;
                sendData->playerCharacterId		= data->playerCharacterId;
 
                // ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_READY_MYSELF_INFO::dataSize );
            }
        }
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignListFromClient( I32 id, PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
        if (player.isNull())
        {
            //
            return;
        }
		SClan* clan;// = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			return;
		}

		sendCampaignListToCenterServer(player->getClientNetID());
		//std::map<ClanIdType, SCampaign*>* campaignList = CampaignManager::getInstance().getPrepareCampaignList();

		//sendCampaignListToClient(player->getClientNetID(), campaignList);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignErrorToClient(NetIdType clientNetID, CAMPAIGN_ERROR error)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_ERROR;

			// ת���߼���
			PT_CAMPAIGN_T2C_ERROR_DATA* sendData = (PT_CAMPAIGN_T2C_ERROR_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->error = error;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_ERROR_INFO::dataSize, 
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignLeaveInCampaignToClient(NetIdType clientNetID, CampaignIdType campaignId)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
		FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN;

			// ת���߼���
			PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA* sendData = (PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->campaignId = campaignId;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_INFO::dataSize, 
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignListToCenterServer(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2T_CAMPAIGN_LIST;

			// ת���߼���
			PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA* sendData = (PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->clientNetId = clientNetID;
				// ��������
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2T_CAMPAIGN_LIST_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnterDefenseFromCenterServer(I32 id , PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA* data)
	{
		//SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(data->);
		//DYNAMIC_ASSERT(NULL != region);

		//region->setCampaignId(data->campaignId);
		SPlayerPtr myPlayer;// = SWorldManager::getInstance().getPlayerByAccountId(data->toAccountId);
		if (myPlayer.isNull())return;

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2C_ENTER_DEFENSE;

			// ת���߼���
			PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->toAccountId			= data->toAccountId;
				sendData->campaignId			= data->campaignId;
				sendData->regionId				= data->regionId;
				sendData->regionType			= data->regionType;
				sendData->prepareTimeSecond		= data->prepareTimeSecond;
				
				sendData->newMember.accountId			= data->newMember.accountId;
				sendData->newMember.clanId				= data->newMember.clanId;
				sendData->newMember.playerCharacterId	= data->newMember.playerCharacterId;
				sendData->newMember.position			= data->newMember.position;
				sendData->newMember.readyState			= data->newMember.readyState;
				sendData->newMember.isHost				= data->newMember.isHost;

				sendData->newMember.level			= data->newMember.level;
				sendData->newMember.charArtIcon		= data->newMember.charArtIcon;
				sendData->newMember.hp				= data->newMember.hp;
				sendData->newMember.mp				= data->newMember.mp;

				// ��������
				 FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					 GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_ENTER_DEFENSE_INFO::dataSize,
					 myPlayer->getClientNetID());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnterAttackFromCenterServer(I32 id , PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA* data)
	{
		SPlayerPtr myPlayer;// = SWorldManager::getInstance().getPlayerByAccountId(data->newMember.accountId);
		if (myPlayer.isNull())
		{
			return;
		}

		SPlayerCharacter* myPlayerCharacter;// = myPlayer->getPlayerCharacter(data->newMember.playerCharacterId);
		if (NULL == myPlayerCharacter)
		{
			return;
		}

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2C_ENTER_ATTACK;

			// ת���߼���
			PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* sendData = (PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->campaignId					= data->campaignId;
				sendData->targetRegionId				= data->targetRegionId;
				sendData->newMember.accountId			= data->newMember.accountId;
				sendData->newMember.clanId				= data->newMember.clanId;
				sendData->newMember.playerCharacterId	= data->newMember.playerCharacterId;
				WStrnCpyS(sendData->newMember.playerCharacterName, myPlayerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->newMember.position			= data->newMember.position;
				sendData->newMember.readyState			= data->newMember.readyState;
				sendData->newMember.isHost				= data->newMember.isHost;
				
				sendData->newMember.level				= myPlayerCharacter->getLevel();
				sendData->newMember.charArtIcon			= myPlayerCharacter->getData()->charArtIcon;
				sendData->newMember.hp					= myPlayerCharacter->getHp();
				sendData->newMember.mp					= myPlayerCharacter->getMp();

				// ��������
				SPlayerPtr toPlayer;// = SWorldManager::getInstance().getPlayerByAccountId(data->toPlayerAccount);
				if (toPlayer.isNull())
				{
					return;
				}

				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2C_ENTER_ATTACK_INFO::dataSize,
					toPlayer->getClientNetID());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStartFromCenterServer(I32 id , PT_CAMPAIGN_T2F_START_DATA* data)
	{
		//SPlayer* myPlayer = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		//if (NULL == myPlayer)
		//{
		//	return;
		//}
		//myPlayer->setCampaignId(data->campaignId);

		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);

		region->setCampaignId(data->campaignId);

		sendCampaignStartToMapServer(region->getMapServerNetId(),data);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStartJumpRegionFromCenterServer(I32 id , PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA* data)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			return;
		}

		//DYNAMIC_ASSERT(player->getMainClan()->getClanID() == data->clanId);

		PlayerCharacterIdType myPlayerCharacterId;// = player->getMainClan()->getMainGenrealID();
		DYNAMIC_ASSERT(myPlayerCharacterId > 0);
		PlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterJumpToCampaignRegion(myPlayerCharacterId, data);
		PlayerNetPacketProcesser::getInstance().broadcastPlayerJumpToRegion(player, ROT_PLACE, data->toRegionId, data->toInstanceId);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignCreateCampByControlerFromCenterServer(I32 id , PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA* data)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER;

			// ת���߼���
			PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA* sendData = (PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->campaignId				= data->campaignId;
				sendData->targetRegionId			= data->targetRegionId;
				sendData->targetInstanceUId			= data->targetInstanceUId;
				sendData->targetControlerAccountId	= data->targetControlerAccountId;
				sendData->campForce					= data->campForce;
				sendData->campNum					= data->campNum;
				sendData->campIndexStart			= data->campIndexStart;
				
				// ��������
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_INFO::dataSize,
					region->getMapServerNetId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignChangeCampOwnerByControlerFromCenterServer(I32 id , PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA* data)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER;

			// ת���߼���
			PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA* sendData = (PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->targetRegionId		= data->targetRegionId;
				sendData->targetInstanceUId		= data->targetInstanceUId;
				sendData->accountId				= data->accountId;
				//sendData->campForce					= data->campForce;
				//sendData->campNum					= data->campNum;
				//sendData->campIndexStart			= data->campIndexStart;
		
				// ��������
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_INFO::dataSize,
					region->getMapServerNetId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignTroopControllerListFromCenterServer(I32 id , PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA* data)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST;

			// ת���߼���
			PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA* sendData = (PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->myAccountId					= data->myAccountId;
				sendData->targetRegionId				= data->targetRegionId;
				sendData->targetInstanceUId				= data->targetInstanceUId;
				sendData->campId						= data->campId;
				sendData->campOwnerAccountId			= data->campOwnerAccountId;
				sendData->troopCurControllerAccountId	= data->troopCurControllerAccountId;
				
				sendData->addMemberNum					= data->addMemberNum;
				
				// TODO: ����AccountId����ȷ ��ҪС��ȷ�� king
				//SPlayerPtr playerPtr = SWorldManager::getInstance().getPlayerByAccountId(data->myAccountId);
				
				for (Int i=0; i<sendData->addMemberNum; ++i)
				{
					
					
					AccountIdType accountId = data->addMemberInfo[i].accountId;
					PlayerCharacterIdType tempPlayerCharId = data->addMemberInfo[i].playerCharacterId;

					SPlayerCharacter* tempPlayerCharacter;// = SWorldManager::getInstance().getPlayerCharacter(accountId, tempPlayerCharId);
					DYNAMIC_ASSERT(NULL != tempPlayerCharacter);

					sendData->addMemberInfo[i].accountId			= accountId;
					sendData->addMemberInfo[i].playerCharacterId	= tempPlayerCharId;
					sendData->addMemberInfo[i].templateId			= tempPlayerCharacter->getCharacterTemplateID();
					sendData->addMemberInfo[i].charArtIcon			= tempPlayerCharacter->getData()->charArtIcon;
					WStrnCpyS(sendData->addMemberInfo[i].playerCharacterName, data->addMemberInfo[i].playerCharacterName, MAX_CHARACTER_NAME_LEN);
				}
				
				// ��������
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA_INFO::dataSize(sendData),
					region->getMapServerNetId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignLeaveInCampaignFromCenterServer(I32 id , PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA* data)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			return;
		}

		player->setCampaignId(0);
		sendCampaignLeaveInCampaignToClient(player->getClientNetID(), data->campaignId);
		SPlayerCharacter* playerCharacter;// = player->getMainClan()->getMainPlayerCharacter();
		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToRegionNewVer(playerCharacter, 
			playerCharacter->getLastRegionType(), playerCharacter->getLastRegionId(), playerCharacter->getLastInstanceUId());
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEndFromCenterServer(I32 id , PT_CAMPAIGN_T2F_END_DATA* data)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->targetRegionId);
		DYNAMIC_ASSERT(NULL != region);
		region->setCampaignId(0);
		

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_F2M_END;

		// ת���߼���
		PT_CAMPAIGN_F2M_END_DATA* sendData = (PT_CAMPAIGN_F2M_END_DATA*)(packet->data);
		if ( sendData )
		{
			//����߼���
			sendData->targetRegionId		= data->targetRegionId;
			sendData->targetInstanceUId		= data->targetInstanceUId;
			sendData->campaignId			= data->campaignId;
			sendData->fromRegionId			= data->fromRegionId;
			sendData->winnerForce			= data->winnerForce;
			
			// ��������
			ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_F2M_END_INFO::dataSize, 
				region->getMapServerNetId());
		}

	}

	//--------------------------------------------------------------------------
}