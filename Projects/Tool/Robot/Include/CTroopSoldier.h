/******************************************************************************/
#ifndef _CTROOPSOLDIERENTITY_H_
#define _CTROOPSOLDIERENTITY_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
//#include "CCharacterSceneEntity.h"
#include "CTroopObject.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //ะกื้สฟฑ๘สตฬๅ
    /******************************************************************************/
	class CTroopObject;

	class CTroopSoldier : public GameObject
    {
    public:

        CTroopSoldier(CTroopObject* owner);
        virtual ~CTroopSoldier();

    public:

        //กมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกม
        //  [ึ๗าชทฝทจ]
        //กมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกม

        // ณ๕สผปฏ
        virtual void				        initialize();
        // ทดณ๕สผปฏ
        virtual void				        unInitialize();

        //กมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกม
        //  [ป๙ดกส๔ะิ]
        //กมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกมกม

        // ตรตฝป๙ดกส๔ะิ
        TroopSoldierData*		            getBaseData();  

		CCharacterSceneEntityDynamicData*	getDynamicData(){return mCharacterDynamicData;}
        // ตรตฝะกื้ถิฯ๓
        CTroopObject*                       getTroopEntity(){return mTroopEntity;}

		void								setPos(Vec3 pos){ mPos = pos;}
		Vec3&								getPos(){return mPos;}
    protected:

      

    private:
		CCharacterSceneEntityDynamicData*	mCharacterDynamicData;

        CTroopObject*						mTroopEntity;
		
		Vec3								mPos;
    };
}

#endif
