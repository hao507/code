/******************************************************************************/
#ifndef _H_SYSLOGNETPACKETPROCESSER_
#define _H_SYSLOGNETPACKETPROCESSER_
/******************************************************************************/
#include "SysLogNetPacket.h"
#include "SPlayer.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //�ʺŵ�����Ϣ����
    /******************************************************************************/
    class SysLogNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SysLogNetPacketProcesser);

	public:
		//����Account������Ϣ��SysLogServer
		void	sendCharacterInfoToSysLogServer(I32 id, I32 clientNetId, Byte type, IdType accountID, PlayerCharacterIdType characterId, Str16 name, Str16 surname);
        void	sendCharacterListInfoToSysLogServer(SPlayerPtr pPlayer, Bool isLoad = true);

    };
}
#endif