/*
 * One method is using two lists, with all threads using the lists.
 * The father thread can know whether son threads is waiting and can wait until some son threads is in wait state.
 * The way need to using some synchronizations.
 * For example, all son threads need to write the lists, and father thread too.
 * As well as, maybe use semaphore to achieve the fact that father threads wait until some son threads is in wait state.
 *
 * The other method is using condition variable, mutex and semaphore.
 * In this way, all son threads using condition variable to wait to a callable object.
 * When a callable object is existed, condition variable and one of son threads will be awaked by father thread.
 * The amount of semaphore resource and amount of son threads are equal.
 * When one son thread run, it get one semaphore resource. The father thread will wait by semaphore if all son threads are running.
 */

#ifndef ZSynchronization_H
#define ZSynchronization_H

#include <list>
extern "C"
{
#include <semaphore.h>
}
#include "ZThread.h"
#include "ZRunnable.h"
using uint = unsigned int;
using std::list;

class ZSynchronization
{
public:
    ZSynchronization(uint amount, error_t *err = nullptr);
    ~ZSynchronization();

    void run(const list<Fnt> &l);
    void run(const Fnt &f);
    uint amount() const;

    int wait();

private:
    uint mAmount;
    sem_t mSem;
};

#endif // ZSynchronization_H
