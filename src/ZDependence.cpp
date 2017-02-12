#include "ZDependence.h"

ZDependence::ZDependence() : mDependences({this})
{
    ;
}

bool ZDependence::empty() const
{
    return mWorks.empty();
}

void ZDependence::push(const Fnt &f)
{
    mWorks.push_back(f);
}

void ZDependence::push(const ZRunnable &runnable)
{
    push(Fnt([&](){runnable.run();}));
}

void ZDependence::push(ZRunnable &runnable)
{
    push(Fnt([&](){runnable.run();}));
}

bool ZDependence::pushSub(const ZDependence &dependence)
{
    if (this == &dependence)
    {
        return false;
    }
    if (!valid(dependence))
    {
        return false;
    }

    mDependences.insert(dependence.mDependences.begin(),dependence.mDependences.end());
    mSubs.push_back(&dependence);
    return true;
}

ZDependence::iterator ZDependence::begin() const
{
    return iterator(*this);
}

ZDependence::iterator ZDependence::end() const
{
    return iterator();
}

bool ZDependence::valid(const ZDependence &dependence) const
{
    if (this == &dependence)
    {
        return false;
    }
    if (dependence.mDependences.find(this) != dependence.mDependences.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

ZDepIterator::ZDepIterator()
{
    mEnd = true;
}

ZDepIterator::ZDepIterator(const ZDependence &dependence)
{
    initSave(dependence);
    mEnd = mDependencePool.empty();
    mCurrent = mDependencePool.crbegin();
}

const list<Fnt> &ZDepIterator::operator *() const
{
    return *mCurrent;
}

const list<Fnt> *ZDepIterator::operator ->() const
{
    return & this->operator *();
}

ZDepIterator &ZDepIterator::operator ++()
{
    ++mCurrent;
    if (mCurrent == mDependencePool.crend())
    {
        mEnd = true;
    }
    return *this;
}

const ZDepIterator ZDepIterator::operator ++(int)
{
    ZDepIterator it(*this);
    this->operator ++();
    return it;
}

void ZDepIterator::initSave(const ZDependence &dependence)
{
    queue<const ZDependence *> deps1({&dependence});
    queue<const ZDependence *> deps2;
    list<Fnt> fnts;

    while (!deps1.empty() || !deps2.empty())
    {
        fnts.clear();
        while (!deps1.empty())
        {
            const ZDependence *dep = deps1.front();
            for (const ZDependence *each : dep->mSubs)
            {
                deps2.push(each);
            }
            for (const Fnt &each : dep->mWorks)
            {
                fnts.push_back(each);
            }
            deps1.pop();
        }
        if (!fnts.empty())
        {
            mDependencePool.push_back(fnts);
        }

        fnts.clear();
        while (!deps2.empty())
        {
            const ZDependence *dep = deps2.front();
            for (const auto &each : dep->mSubs)
            {
                deps1.push(each);
            }
            for (const auto &each : dep->mWorks)
            {
                fnts.push_back(each);
            }
            deps2.pop();
        }
        if (!fnts.empty())
        {
            mDependencePool.push_back(fnts);
        }
    }
}

bool operator ==(const ZDepIterator &itor1, const ZDepIterator &itor2)
{
    return (itor1.mEnd == itor2.mEnd) || (itor1.mCurrent == itor2.mCurrent);
}

bool operator !=(const ZDepIterator &itor1, const ZDepIterator &itor2)
{
    return !operator ==(itor1,itor2);
}
