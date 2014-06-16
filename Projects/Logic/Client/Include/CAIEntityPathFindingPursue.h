/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGPURSUE_H_
#define _CAIENTITYPATHFINDINGPURSUE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************

	******************************************************************************/
	class CAIEntityPathFindingPursue : public CAI, public LinedStateObject
	{
	public:
		CAIEntityPathFindingPursue( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityPathFindingPursue();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        							update( Flt delta );
		///是否结束了
		virtual Bool        							isFinished();
		///进去状态事件
		virtual void        							onEnter();
		///离开状态事件
		virtual void        							onLeave();

	public:

		//设置目标
		void											setTarget( Vec3 pos );
		void											setTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		////////////////////////////////////////////////////////////////////////

		void											setPursueRadius( Flt pursueRadius );

		void											setStopPursueRadius( Flt stopPursueRadius );

	protected:

		void											updatePursue( Flt delta );

		// 停止思考
		void											stopThink( Flt time );
		// 恢复思考
		void											resumeThink();

		////////////////////////////////////////////////////////////////////////
		void											notifyPursueResult( Bool isFinish );

		void											notifyTargetDied();

	private:

		CAIEntityPathFindingMoveInAdvance*				mPathFindingMoveAI;
		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		Bool											mIsFinished;
		Vec3											mMoveToPos;
		Vec3											mLastTargetPos;
		Int												mBlockDiameter;
		Flt												mPauseThinkTime;
		Flt												mPursueRadius;
		Vec3											mPoint;
		Flt												mStopPursueRadius;
	};
}

#endif