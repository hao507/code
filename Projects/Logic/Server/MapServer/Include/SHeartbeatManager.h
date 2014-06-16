/******************************************************************************/
#ifndef _SHEARTBEATMANAGER_H_
#define _SHEARTBEATMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // ����������
    /******************************************************************************/
    class SHeartbeatManager
    {
    public:		
        SHeartbeatManager();
        virtual ~SHeartbeatManager();
        SINGLETON_INSTANCE(SHeartbeatManager);
        

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        Bool                initialize();
        Bool                unInitialize();

        static void         updateLogicHeartbeatThread(Ptr ptr);

        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------


        void                addPlayerHeartbeat(SPlayerPtr& ptr);
        Bool                updatePlayerHeartbeat(Flt delta);


        //-----------------------------------------------------------------------------------
        // Region
        //-----------------------------------------------------------------------------------



    private:

        std::list<SPlayerPtr> mSPlayerPtrList;
        Critical    mSPlayerPtrListCs;

    };

}

#endif