//******************************************************************************************
#ifndef _H_MGRANDOM_
#define _H_MGRANDOM_
//******************************************************************************************

#include "Singleton.h"

namespace  MG
{
    class MGRandom
    {
    public:
        MGRandom();
        ~MGRandom();
        SINGLETON_INSTANCE(MGRandom);

    public:
        //��á�a, b��֮���һ���������,   a<b
        U32 rand_ab_One(U32 min, U32 max);
		//ͨ��2D�����ȡperlin��������ָ
		I32 rand_perlin_2d( U32 x, U32 y );
		//ͨ��2D�����ȡperlin�������ָָ����¶�
		Vec3 rand_gradients_2d( U32 x, U32 y );
    };
}
//******************************************************************************************
#endif  //_H_MGRANDOM_
//******************************************************************************************