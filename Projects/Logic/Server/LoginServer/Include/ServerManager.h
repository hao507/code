/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/

/******************************************************************************/
class SServerSetting;
namespace MG
{

	/******************************************************************************/
	//FrontServer����
	/******************************************************************************/
	struct FrontServerInfo 
	{
		I32		netId;
		UInt	clientNum;
		Str		listenClientIp;
		I32		listenClientPort;
        Bool	isValid;
		FrontServerInfo()
		{
			listenClientPort	= 0;
			clientNum			= 0;	
            isValid             = false;
		}
	};
	/******************************************************************************/
	//������������������֮���ӵ�FrontServer����ز���
	/******************************************************************************/
	class ServerManager
	{
	public:
		SINGLETON_INSTANCE(ServerManager);
		ServerManager();
		virtual ~ServerManager();
	public:

		//��ʼ���ͷ���ʼ��
		Bool				initialize();
		void				uninitialize();

		//�����̸���
		void				update();
	
		//����ײ��¼�
		void				onConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		void				onDisconnect(I32 id);
		Bool				processPacket(I32 id,NetEventRecv* packet);

		//���Ӻ��Ƴ�FrontServer����
        FrontServerInfo*    getFrontServer(I32 netId);                
        void				addFrontServer(I32 netId);
		void				addFrontServer(I32 netId, CChar*	ip, I32 port);
		void				removeFrontServer(I32 netId);

		//����һ���������ٵ�FrontServer�����ڿͻ��˵���
		FrontServerInfo*	allocClientConnect();
		void				freeClientConnect(I32 netId);

        //������־������������ID��
        void                setSysLogServerNetID(I32 netID);
        I32                 getSysLogServerNetID(){return mSysLogServerNetID;}

	protected:

		/*
			# FrontServer���С�
			# ��FrontServer�Ͽ�ʱ��Ҫ��տͻ������ж�����ش�FrontServer�����пͻ��˶���
		*/
		std::map< I32, FrontServerInfo >    mFrontServerList;
        //��־������������ID
        I32                                 mSysLogServerNetID;
	};
}
#endif