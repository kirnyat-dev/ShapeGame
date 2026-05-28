#ifndef _SCEENWORKER_H_
#define _SCEENWORKER_H_

#include "Sceen.h"

class SceenWorker
{
public:
    virtual void MakePlate(Sceen* product) = 0;
    virtual void MakeToys(Sceen* product) = 0;
    virtual void Checkout(Sceen* product) = 0;
    virtual ~SceenWorker() = default;
};

#endif