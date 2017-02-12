/*
 * Using one list to save a dependent relationship in one ZDependence class.
 * When adding new dependent relationship, such as callable object, ZRunnable class or the other ZDependence class, the list will be update.
 * Using iterator to dependently get callable objects.
 */

#ifndef ZDEPENDENCE_H
#define ZDEPENDENCE_H

#include <functional>
#include <list>
#include <set>
#include <queue>
#include "ZRunnable.h"

class ZDependence;
class ZDepIterator;

using std::list;
using std::set;
using std::queue;
using Fnt = std::function<void ()>;
using SubNode = const ZDependence *;

class ZDependence
{
    friend class ZDepIterator;
public:
    using iterator = ZDepIterator;

    ZDependence();

    bool empty() const;
//    const Fnt &next();
    void push(const Fnt &f);
    void push(const ZRunnable &runnable);
    void push(ZRunnable &runnable);

    bool pushSub(const ZDependence &dependence);

    //iterator operations
    iterator begin() const;
    iterator end() const;

private:
    bool valid(const ZDependence &dependence) const;

private:
    list<Fnt> mWorks;
    list<SubNode> mSubs;
    set<const ZDependence *> mDependences;
};

class ZDepIterator
{
    using SaveType = list<list<Fnt>>;
    using OutsideIter = list<list<Fnt>>::const_reverse_iterator;
    using InsideIter  = list<Fnt>::const_reverse_iterator;
    friend bool operator ==(const ZDepIterator &itor1, const ZDepIterator &itor2);
    friend bool operator !=(const ZDepIterator &itor1, const ZDepIterator &itor2);
public:
    ZDepIterator();
    ZDepIterator(const ZDependence &dependence);

    const list<Fnt> &operator *() const;
    const list<Fnt> *operator ->() const;
    ZDepIterator &operator ++();
    const ZDepIterator operator ++(int);

private:
    void initSave(const ZDependence &dependence);
private:
    bool mEnd;
    SaveType mDependencePool;
    OutsideIter mCurrent;
};

bool operator ==(const ZDepIterator &itor1, const ZDepIterator &itor2);
bool operator !=(const ZDepIterator &itor1, const ZDepIterator &itor2);

#endif // ZDEPENDENCE_H
