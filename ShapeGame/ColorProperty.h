#ifndef _COLORPROPERTY_H_
#define _COLORPROPERTY_H_

#include "Property.h"

class ColorProperty : public Property
{
public:
    enum class Color
    {
        Red,
        Green,
        Blue,
        Yellow
    };

    ColorProperty(Color color) : color(color) {}

    bool matches(const Property& other) const override
    {
        const ColorProperty* otherColor = dynamic_cast<const ColorProperty*>(&other);
        return otherColor != nullptr && color == otherColor->color;
    }

    std::string getDescription() const override
    {
        switch (color)
        {
        case Color::Red:    return "red";
        case Color::Green:  return "green";
        case Color::Blue:   return "blue";
        case Color::Yellow: return "yellow";
        }
        return "unknown";
    }

    std::unique_ptr<Property> clone() const override
    {
        return std::make_unique<ColorProperty>(color);
    }

private:
    Color color;
};

#endif