#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>
#include <memory>

class Property
{
public:
    virtual ~Property() = default;
    virtual bool matches(const Property& other) const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::unique_ptr<Property> clone() const = 0;
};

#endif