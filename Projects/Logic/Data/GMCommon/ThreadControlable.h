/******************************************************************************/
#ifndef _THREADCONTROLABLE_H_
#define _THREADCONTROLABLE_H_
/******************************************************************************/
#include "Lock.h"
/******************************************************************************/
//class ThreadControlable 
/******************************************************************************/
class ThreadControlable
{
public:
    void    lock(){m_CriSec.lock();}
    void    unLock(){m_CriSec.unlock();}
protected:
	MG::Critical	 m_CriSec;
};

/******************************************************************************/

#endif 

