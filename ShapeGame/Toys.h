#ifndef _TOYS_H_
#define _TOYS_H_

#include <memory>
#include "ItemProperties.h"

class Toys
{
public:
    explicit Toys(std::unique_ptr<ItemProperties> props) : properties(std::move(props)) {}

    const ItemProperties& getProperties() const
    {
        return *properties;
    }

private:
    std::unique_ptr<ItemProperties> properties;
};

#endif