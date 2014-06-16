/******************************************************************************/
#ifndef _CAI_H_
#define _CAI_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "AI.h"
/******************************************************************************/

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//AI
	/******************************************************************************/
	class CAI : public AI
	{
	public:
		CAI( CCharacterSceneEntity* owner );
		virtual ~CAI();

	protected:
		CCharacterSceneEntity* mOwner;
	};
}


#endif	