/******************************************************************************/
#include "stdafx.h"
#include "SysLogNetPacketProcesser.h"
#include "SPlayer.h"
#include "SClan.h"
#include "SPlayerCharacter.h"
#include "FrontServerMain.h"
#include "ClientManager.h"
#include "NetAddress.h"
#include "ServerManager.h"
/******************************************************************************/
namespace MG
{
	//-------------------------------------------------------------------------------
	void SysLogNetPacketProcesser::sendCharacterInfoToSysLogServer( I32 id, I32 clientNetId, Byte type, IdType accountID, PlayerCharacterIdType characterId, Str16 name, Str16 surname )
	{
		if (-1 == id) return;
		///////////////////////////////////////////////////////////////////////////

		// ���һ�����͡�������������
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_SYSLOG;
			packet->type    = PT_SYSLOG_CHARACTER_LOGIN;

			// ת���߼���
			PT_SYSLOG_CHARACTER_LOGIN_Data* sendData = (PT_SYSLOG_CHARACTER_LOGIN_Data*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->characterId = characterId;
				sendData->type = type;
				swprintf_s(sendData->name, MAX_CHARACTER_NAME_LEN, L"%s", name.c_str());
				swprintf_s(sendData->surName, MAX_CHARACTER_NAME_LEN, L"%s", surname.c_str());
				sendData->playerId = accountID;
				sendData->logTime = MGTimeOp::getCurrTimestamp();
				ClientObject* pClientObject;// = ClientManager::getInstance().getWaitingLoginClient(clientNetId);
				DYNAMIC_ASSERT(pClientObject);
				sendData->ipAddress;// = pClientObject->ipAddress;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_SYSLOG_CHARACTER_LOGIN_DATA_INFO::dataSize ,
					id );
			}
		}
	}

	//-------------------------------------------------------------------------------
	void SysLogNetPacketProcesser::sendCharacterListInfoToSysLogServer( SPlayerPtr pPlayer, Bool isLoad )
	{
		I32 id;// = ServerManager::getInstance().getSysLogServerNetID();
		if ( -1 == id ) return;

		Byte type = PLAYERCHARACTER_OPERATE_LOGIN;
		if ( isLoad == false )
			type = PLAYERCHARACTER_OPERATE_LOGOUT;

		SClan* clan;// = pPlayer->getMainClan();
		if (NULL == clan) return;
		std::map<U64, SPlayerCharacter*>* playerCharacterList;// = clan->getPlayerCharacterList();
		DYNAMIC_ASSERT(playerCharacterList);
		if ( 0 == playerCharacterList->size() )return;
		
		std::map<U64, SPlayerCharacter*>::iterator frontIter = playerCharacterList->begin();
		std::map<U64, SPlayerCharacter*>::iterator endIter = playerCharacterList->end();
		while (frontIter != endIter)
		{
			sendCharacterInfoToSysLogServer(
				0,//ServerManager::getInstance().getSysLogServerNetID(),
				pPlayer->getClientNetID(), type, pPlayer->getAccountID(),
				frontIter->second->getID(), frontIter->second->getName(), frontIter->second->getData()->charSurName
				);
			
			++frontIter;
		}
	}
}