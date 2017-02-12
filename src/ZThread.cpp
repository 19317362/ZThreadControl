#include "ZThread.h"

ZThread::ZThread(bool detached)
{
    mThread = 0;
    mDetached = detached;
    mRunStatus = STOP;
}

ZThread::~ZThread()
{
    wait();
    mRunStatus = STOP;
}

int ZThread::run(const Fnt &f, void **data)
{
    // the obj will be deleted in pthFunc
    if (mRunStatus == RUN && !mDetached)
    {
        wait(data);
    }
    else if (mRunStatus == RUN && mDetached)
    {
        return -1; // thread is runing and mDetached
    }

    int ret = pthread_create(&mThread,nullptr,thFunc,new Fnt(f));
    if (ret == 0 && mDetached)
    {
        return pthread_detach(mThread);
    }
    else
    {
        return ret;
    }
}

int ZThread::run(const ZRunnable &runnable, void **data)
{
    return run(Fnt([&runnable](){runnable.run();}),data);
}

int ZThread::run(ZRunnable &runnable, void **data)
{
    return run(Fnt([&runnable](){runnable.run();}),data);
}

int ZThread::wait(void **data)
{
    if (mRunStatus == STOP)
    {
        return 0;
    }
    else if (mRunStatus == RUN && !mDetached)
    {
        mRunStatus = STOP;
        return pthread_join(mThread,data); // return error number,change mThread maybe affect running detached thread.
    }
    else // mRunStatus == RUN && mDetached
    {
        return -1;
    }
}

RUN_STATUS ZThread::runStatus() const
{
    return mRunStatus;
}

void ZThread::setRunStatus(const RUN_STATUS &runStatus)
{
    mRunStatus = runStatus;
}

void *thFunc(void *pArg)
{
    // the pArg is Fnt pointer type
    Fnt *pf = static_cast<Fnt*>(pArg);
    if (pf == nullptr)
    {
        throw runtime_error("The callable object is nullptr");
    }
    try
    {
        (*pf)();
    }
    catch (runtime_error &runtime)
    {
        cout << runtime.what() << endl;
    }
    catch (...)
    {
        cout << "unknowable calling error" << endl;
    }
    delete pf;
    return nullptr;
}
