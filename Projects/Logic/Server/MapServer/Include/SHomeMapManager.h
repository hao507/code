
/******************************************************************************/

#ifndef _S_SHOMEMAPMANAGER_H_
#define _S_SHOMEMAPMANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapManager.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  整个家园世界地图管理器
    /******************************************************************************/
    class SHomeMapManager : public SMapManager
    {
    public:

        SHomeMapManager();
        virtual ~SHomeMapManager();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool            initialize(){ return 0; }
        virtual Bool            unInitialize(){ return 0; }
        virtual void            clear(){ return ; }
        virtual void            update(Flt delta){ return ; }

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------
        
		virtual	REGION_OBJ_TYPE getRegionType() const;



    };


}

#endif	