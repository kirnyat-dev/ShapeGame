#ifndef _LEVELBASEDWORKER_H_
#define _LEVELBASEDWORKER_H_

#include "SceenWorker.h"
#include "GameLevel.h"

class LevelBasedWorker : public SceenWorker
{
public:
    explicit LevelBasedWorker(const GameLevel& level) : level(level) {}

    void MakePlate(Sceen* product) override {}
    void MakeToys(Sceen* product) override {}
    void Checkout(Sceen* product) override {}

private:
    GameLevel level;
};

#endif