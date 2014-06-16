/******************************************************************************/
#ifndef _PLAYER_CHARACTER_NET_PACKET_PROCESSER_H_
#define _PLAYER_CHARACTER_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "PlayerCharacterNetPacket.h"
#include "FrontServerPreqs.h"
#include "CampaignNetPacket.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��ɫ���������Ϣ����
    /******************************************************************************/
    class SPlayer;

	class SClanPtr;
    /******************************************************************************/
	class PlayerCharacterNetPacketProcesser
	{
	public:
        SINGLETON_INSTANCE(PlayerCharacterNetPacketProcesser);
		PlayerCharacterNetPacketProcesser();
		~PlayerCharacterNetPacketProcesser();
        
        Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
        
	public:
        
        //-----------------------------------------------------------------------------------
        // Client Packet Handle
        //-----------------------------------------------------------------------------------

		//�����ܵ���ɫ����ͼ
		void onRecvPlayerCharacterJumpRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA*data);

		//��ָ��MapServer�����ִ�
		void onRecvPlayerCharacterJumpTiroRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA*data);

		//�����ܵ���ɫ���ش��ͼ
		void onRecvPlayerCharacterJumpOutRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA*data);

		//��ɫ������һ����ͼ
		void onRecvPlayerCharacterJumpLastRegionFromClient( I32 id , PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA*data);
		

        //-----------------------------------------------------------------------------------
        // Client Packet Send
        //-----------------------------------------------------------------------------------


        void sendAllPlayerCharacterSkillInfoInClanToClient(I32 id,  SClanPtr& clanPtr );

        void sendPlayerCharacterSkillInfoToClient(I32 id, IdType characterId, SSkillOwnManager* skillOwnManager);
        

        //-----------------------------------------------------------------------------------
        // MapServer Packet Handle
        //-----------------------------------------------------------------------------------

		//�յ���ɫ��ת��Ϣ
		void onRecvPlayerCharacterJumpRegionFromMapServer(I32 id, PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA* data);


        //-----------------------------------------------------------------------------------
        // MapServer Packet Send
        //-----------------------------------------------------------------------------------

        //���ͽ�ɫ�ƶ���Ϣ
		void sendPlayerCharacterMoveToMapServer(I32 id, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data );
        /************************************************************************************************/
		//�°汾 ����ͼ 2012.12.01
		void sendPlayerCharacterJumpToRegionNewVer(SPlayerCharacter* playerCharacter, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId, Int pointId = 0, NetIdType mapServerNetId = 0);
	
		void sendPlayerCharacterJumpRegionByMapServerNetIdNewVer(SPlayerCharacter* playerCharacter, NetIdType mapServerNetId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId, Int pointId = 0);
	
		void sendPlayerCharacterJumpToEmptyRegionNewVer(AccountIdType accountId, PlayerCharacterIdType playerCharacterId, NetIdType mapServerNetId);

		/************************************************************************************************/

		//����ս������
		void broadcastPlayerCharacterJumpToCampaignRegion(PlayerCharacterIdType playerCharacterId, PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA* data);
	
		void sendPlayerCharacterJumpRegionToClient(I32 netId, ChatarcterJumpRegionResult result, PlayerCharacterIdType playerCharacterId, RegionIdType regionId, REGION_OBJ_TYPE regionType, InstanceUIdType instanceUId);

		void sendPlayerCharacterrSkillInfoToMapServer(I32 mapserverNetid, IdType characterId, SSkillOwnManager* skillOwnManager );

	protected:

	};

}


#endif