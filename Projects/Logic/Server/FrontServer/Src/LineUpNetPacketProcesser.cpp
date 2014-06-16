/******************************************************************************/
#include "stdafx.h"
#include "GameNetEvent.h"
#include "LineUpNetPacketProcesser.h"
#include "FrontServerMain.h"
#include "ThreadTaskManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	Bool LineUpNetPacketProcesser::processClientPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_LINE_UP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LINE_UP_C2L_CANCLE_CMD:	
				onRecvCancleLineUpCmd(id,(PT_LINE_UP_C2L_CANCLE_CMD_DATA*)data->data);
				break;
			}

			return true;
		}   
		return false;
	}
	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::sendLineUpInfoToClient( I32 netId, Byte type, I32 waitCount /*= 0*/ )
	{

		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_F2C;

			// ת���߼���
			PT_LINE_UP_L2C_DATA* sendData = (PT_LINE_UP_L2C_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->type = type;
				sendData->waitCount = waitCount;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LINE_UP_L2C_DATA_INFO::dataSize,
					netId );
			}
		}
	}

	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::onRecvCancleLineUpCmd(I32 netId,PT_LINE_UP_C2L_CANCLE_CMD_DATA* data)
	{
		LINE_UP_TYPE lineUp = (LINE_UP_TYPE)data->type;
		Bool ret = false;
		switch (data->type)
		{
		case line_up_busy_fc_account_login:
			{
				ret = ThreadTaskManager::getInstance().removePrepareJoinGameTask(netId);
			}
			break;
		case line_up_busy_fc_create_clan:
			{
				ret = ThreadTaskManager::getInstance().removeCreateClanTask(netId);
			}
			break;
		case line_up_busy_fc_del_clan:
			{
				ret = ThreadTaskManager::getInstance().removeDeleteClanTask(netId);
			}
			break;
		case line_up_busy_fc_create_character:
			{
				ret = ThreadTaskManager::getInstance().removeCreateGeneralTask(netId);
			}
			break;
		case line_up_busy_fc_join_game:	
			{
				ret = ThreadTaskManager::getInstance().removeJoinGameTask(netId);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(false);
			}
		}
		sendCancleLineCmdRelustToClient(netId,(Byte)lineUp,ret ? 1 : 0);
	}		

	//-----------------------------------------------------------------------
	void LineUpNetPacketProcesser::sendCancleLineCmdRelustToClient(I32 netId,Byte type,Byte result)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LINE_UP;
			packet->type    = PT_LINE_UP_F2C_CANCLE_CMD_RELULT;

			// ת���߼���
			PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA* sendData = (PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->type = type;
				sendData->result = result;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA_INFO::dataSize,
					netId );
			}
		}
	}
	//-----------------------------------------------------------------------
}