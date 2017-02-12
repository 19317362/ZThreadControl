#include "ZThreadPool.h"

ZThreadPool::ZThreadPool(uint amount) : mThreadSyc(amount)
{
    ;
}

ZThreadPool::~ZThreadPool()
{
    ;
}

uint ZThreadPool::amount() const
{
    return mThreadSyc.amount();
}

void ZThreadPool::run(ZDependence &dependence)
{
    for (auto iter = dependence.begin(); iter != dependence.end(); ++iter)
    {
        mThreadSyc.run(*iter);
    }
    mThreadSyc.wait();
}
