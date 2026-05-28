#ifndef _FRAMES_H_
#define _FRAMES_H_

#include <memory>
#include "ItemProperties.h"
#include "Toys.h"

class Frames
{
public:
    explicit Frames(std::unique_ptr<ItemProperties> props) : properties(std::move(props)) {}

    bool IsPassable(const Toys& toy, int propertiesCount) const
    {
        return properties->matches(toy.getProperties(), propertiesCount);
    }

    const ItemProperties& getProperties() const
    {
        return *properties;
    }

private:
    std::unique_ptr<ItemProperties> properties;
};

#endif