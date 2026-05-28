#ifndef _SHAPEPROPERTY_H_
#define _SHAPEPROPERTY_H_

#include "Property.h"
#include "Form.h"

class ShapeProperty : public Property
{
public:
    explicit ShapeProperty(const Form& form) : form(form) {}

    bool matches(const Property& other) const override
    {
        const ShapeProperty* otherShape = dynamic_cast<const ShapeProperty*>(&other);
        if (!otherShape) return false;
        return form.IsEqual(otherShape->form);
    }

    std::string getDescription() const override
    {
        return form.GetName();
    }

    std::unique_ptr<Property> clone() const override
    {
        return std::make_unique<ShapeProperty>(form);
    }

private:
    Form form;
};

#endif