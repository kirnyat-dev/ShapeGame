#ifndef _SCEENDIRECTOR_H_
#define _SCEENDIRECTOR_H_

#include "Sceen.h"
#include "SceenWorker.h"

class SceenDirector
{
public:
    SceenDirector() : product(nullptr), worker(nullptr) {}
    SceenDirector(Sceen* product, SceenWorker* worker) : product(product), worker(worker) {}
    explicit SceenDirector(SceenWorker* worker) : product(nullptr), worker(worker) {}

    void SetWorker(SceenWorker* worker) { this->worker = worker; }
    void SetProduct(Sceen* product) { this->product = product; }

    void Produce()
    {
        if (worker && product)
        {
            worker->MakePlate(product);
            worker->MakeToys(product);
            worker->Checkout(product);
        }
    }

    Sceen* GetProduct() { return product; }
    Sceen* ReleaseProduct()
    {
        Sceen* p = product;
        product = nullptr;
        return p;
    }

private:
    Sceen* product;
    SceenWorker* worker;
};

#endif