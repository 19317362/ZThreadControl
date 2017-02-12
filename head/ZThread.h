/* Using thread in linux.
 * ZThread Class can create thread to run user's functions that include general function,
 * lambda, member function pointer, etc.
 * The form of functions is "void function();"
 */
/* ZThread need a object to control resources including function of user. The resources created
 * before thread, and deleted when thread over. The object can be tupid or class and etc.
 *
 */
#ifndef ZTHREAD_H
#define ZTHREAD_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include "ZRunnable.h"

using std::function;
using std::runtime_error;
using std::cout;
using std::endl;
using Fnt = function<void ()>;

enum RUN_STATUS{STOP = 0,RUN};

/*=>using smart pointer
 * pArg is pointer type, and argument isn't object. Maybe smart pointer counter will not increase.
 * Wait for implementation...
 */
void *thFunc(void *pArg);

class ZThread
{
public:
    ZThread(bool detached = false);
    ~ZThread();

    int run(const Fnt &f,void **data = nullptr);
    int run(const ZRunnable &runnable,void **data = nullptr);
    int run(ZRunnable &runnable,void **data = nullptr);

    int wait(void **data = nullptr);

    RUN_STATUS runStatus() const;

protected:
    void setRunStatus(const RUN_STATUS &runStatus);

private:
    pthread_t mThread;
    bool mDetached;
    RUN_STATUS mRunStatus;
};

#endif // ZTHREAD_H
