#ifndef ZRUNNABLE_H
#define ZRUNNABLE_H

#include <stdexcept>
using std::runtime_error;

class ZRunnable
{
public:
    ZRunnable() = default;
    virtual void run();
    virtual void run() const;
    virtual ~ZRunnable() = default;
};

#endif // ZRUNNABLE_H
