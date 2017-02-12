#include "ZRunnable.h"

void ZRunnable::run()
{
    throw runtime_error("call ZRunnable run");
}

void ZRunnable::run() const
{
    throw runtime_error("call const ZRunnable run");
}
