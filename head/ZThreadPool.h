/*
 * This thread pool has the function that supports the dependent relationship.
 *
 * The thread pool can be achieved using two classes.
 * One can control dependence and is named ZDependence.
 * The other can control the synchronization of multi-threads and is named ZThreadSyc.
 */
#ifndef ZThreadPool_H
#define ZThreadPool_H
#define DEFAULT_AMOUNT 1

#include "ZSynchronization.h"
#include "ZDependence.h"
using uint = unsigned int;

class ZThreadPool
{
public:
    ZThreadPool(uint amount = DEFAULT_AMOUNT);
    ~ZThreadPool();
    uint amount() const;
    void run(ZDependence &dependence);

private:
    ZSynchronization mThreadSyc;
};

#endif // ZThreadPool_H
