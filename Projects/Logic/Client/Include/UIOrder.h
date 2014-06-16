//***************************************************************************************************
#ifndef _H_UIORDER_
#define _H_UIORDER_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIOrder  : public UIObject
    {
    public:
        UIOrder();
        ~UIOrder();
        SINGLETON_INSTANCE(UIOrder);

    public:
        virtual void setEvent();

    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************