//**********************************************************************************************************
#ifndef _H_BUYBACKITEMS_
#define _H_BUYBACKITEMS_
//**********************************************************************************************************
#include "Items.h"
//**********************************************************************************************************
namespace MG
{
	class BuyBackItem : public Items
	{
	public:
		BuyBackItem();
		virtual ~BuyBackItem(){;}

	public:
		//����
		void        addItem(PlayerItem* pItem, Bool isServer);


	};
}




//**********************************************************************************************************
#endif
//**********************************************************************************************************