#ifndef _ITEMPROPERTIES_H_
#define _ITEMPROPERTIES_H_

#include <vector>
#include <memory>
#include "Property.h"

class ItemProperties
{
public:
    void addProperty(std::unique_ptr<Property> prop)
    {
        properties.push_back(std::move(prop));
    }

    bool matches(const ItemProperties& other, int count) const
    {
        int n = count;
        if (n > (int)properties.size()) n = properties.size();
        if (n > (int)other.properties.size()) n = other.properties.size();
        for (int i = 0; i < n; ++i)
        {
            if (!properties[i]->matches(*other.properties[i]))
            {
                return false;
            }
        }
        return true;
    }

    std::string getDescription() const
    {
        std::string desc;
        for (const auto& p : properties)
        {
            if (!desc.empty()) desc += ", ";
            desc += p->getDescription();
        }
        return desc;
    }

    std::unique_ptr<ItemProperties> clone() const
    {
        auto newProps = std::make_unique<ItemProperties>();
        for (const auto& p : properties)
        {
            newProps->addProperty(p->clone());
        }
        return newProps;
    }

private:
    std::vector<std::unique_ptr<Property>> properties;
};

#endif