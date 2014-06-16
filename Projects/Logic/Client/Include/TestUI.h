//**************************************************************************************************
#ifndef _H_TESTUI_578493jgkdfl_
#define _H_TESTUI_578493jgkdfl_
//**************************************************************************************************

#include "ClientPreqs.h"

//**************************************************************************************************

namespace MG
{
    class  TestUI
    {
    public:
        TestUI();
        ~TestUI();
        SINGLETON_INSTANCE(TestUI);
    public:
        Bool init();
        Bool update();
    };
}

//**************************************************************************************************
#endif
//**************************************************************************************************