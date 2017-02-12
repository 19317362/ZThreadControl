#include "ZSynchronization.h"

ZSynchronization::ZSynchronization(uint amount, error_t *err)
{
    mAmount = amount;
    int ret = sem_init(&mSem,0,mAmount);
    if (ret == -1 && err != nullptr)
    {
        *err = errno;
    }
    else if (ret == 0 && err != nullptr)
    {
        *err = 0;
    }
}

ZSynchronization::~ZSynchronization()
{
    wait();
    sem_destroy(&mSem);
}

void ZSynchronization::run(const list<Fnt> &l)
{
    for (const auto &each : l)
    {
        run(each);
    }
}

void ZSynchronization::run(const Fnt &f)
{
    sem_wait(&mSem);
    ZThread thread(true);
    thread.run(Fnt([&]()
                  {
                      f();
                      sem_post(&mSem);
                  }
                ));
}

uint ZSynchronization::amount() const
{
    return mAmount;
}

int ZSynchronization::wait()
{
    int ret = 0;
    uint times = 0;
    do
    {
        ret = sem_wait(&mSem);
    }while (++times < mAmount && ret == 0);

    while (times-- && ret == 0)
    {
        ret = sem_post(&mSem);
    }
    return ret;
}
