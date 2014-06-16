
/******************************************************************************/

#ifndef _S_ATKMAPOBJECT_H_
#define _S_ATKMAPOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SMapObject.h"
#include "SSceneObjectFactory.h"
#include "SPlaceSceneObject.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  ���ǵ�ͼ������
    /******************************************************************************/
    class SPlaceMapObject : public SMapObject
    {
    public:
        SPlaceMapObject(PlaceListCsvInfo* placeListCsvInfo, DistrictIdType districtId);
        virtual ~SPlaceMapObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        //virtual Bool                initialize();
        //virtual Bool                unInitialize();
        //virtual void                clear();
        //virtual void                update(Flt delta);

        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------
		PlaceListCsvInfo*			getPlaceListCsvInfo();

		virtual	DistrictIdType		getDistrictId();		//�󶨵�����ID
		virtual DistrictRankType	getDistrictRankType();		//����������
		virtual RegionIdType		getRegionId();

		PlaceObjectData*			getPlaceData();
		DistrictListCsvInfo*		getDistrictListCsvInfo();

		
        //-----------------------------------------------------------------------------------
        // Scene
        //-----------------------------------------------------------------------------------

        //�����б�
		void		                createScene(SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		Bool		                getScene(SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid);
		void		                destroyScene(InstanceUIdType instanceUid);
		void		                destroyAllScene();

		//����
		void		                createMainScene(SPlaceSceneObjectPtr& ptr);
		Bool		                getMainScene(SPlaceSceneObjectPtr& ptr);
		void		                destroyMainScene();
    
	private:

		PlaceListCsvInfo*		mPlaceListCsvInfo;

		// �����Ǹ�����ͼ������
		SPlaceSceneObjectFactory  mPlaceSceneObjectFactory;

		//�����Ǹ�����ͼ���б�
		std::map<InstanceUIdType,SPlaceSceneObjectPtr> mSAtkSceneObjecList;

		//����
		SPlaceSceneObjectPtr  mMainAtkSceneObject;

		RWLocker    mSAtkSceneObjectListCs;


	private:
		SPlaceMapObject();
    };


}

#endif	