#include "ZThread.h"

ZThread::ZThread(bool detached)
{
    mThread = 0;
    mDetached = detached;
}

ZThread::~ZThread()
{
    wait();
}

int ZThread::run(const Fnt &f, void **data)
{
    // the obj will be deleted in pthFunc
    wait(data);
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
    if (mDetached)
    {
        return 0;
    }
    return pthread_join(mThread,data); // return error munber,change mThread maybe affect running detached thread.
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
