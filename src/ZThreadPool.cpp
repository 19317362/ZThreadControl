#include "ZThreadPool.h"

ZThreadPool::ZThreadPool(uint amount)
    // Controls the maximum number of threads that can run
    : mThreadSyc(amount)
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
        // Waiting for a group of peer-level dependencies to complete
        mThreadSyc.wait();
    }
}
