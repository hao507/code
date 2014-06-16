/******************************************************************************/
#ifndef _SCHARACTERMOVETOACTION_H_
#define _SCHARACTERMOVETOACTION_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	//游戏对象移动行为
	/******************************************************************************/
	class SCharacterMoveToAction : public LinedStateObject
	{
	public:
		SCharacterMoveToAction( SCharacter* character, Vec3 startMovePos, Vec3 moveToPos );
		virtual ~SCharacterMoveToAction();

	public:

		//状态名字
		//static Str STATE_NAME = "";
#define STATE_NAME "dfefefe"

		///更新事件
		virtual void        update( Flt delta );
		///是否结束了
		virtual Bool        isFinished();
		///进去状态事件
		virtual void        onEnter();
		///离开状态事件
		virtual void        onLeave();

		////////////////////////////////////////////////////////////////////////////////////

		void				setMoveSpeed( Flt speed );

		Vec3				getMoveToPos();

	private:

		SCharacter*			mCharacter;

		Vec3				mStartMovePos;
		Vec3				mMoveToPos;
		Vec3				mMoveToDir;

		Flt					mCurrMoveTime;
		
		Flt					mMoveSpeed;

		Flt					mMoveTimeLength;

		Flt					mMoveDis;

	};
}

/******************************************************************************/

#endif //