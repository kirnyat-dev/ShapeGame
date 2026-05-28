#ifndef _FORM_H_
#define _FORM_H_

#include <string>
#include <iostream>

class Form
{
public:
    enum class Shapes
    {
        circle,
        triangle,
        square,
        star
    };

    Form(Shapes shape)
    {
        this->shape = shape;
        switch (shape)
        {
        case Shapes::circle:
            this->name = "circle";
            break;
        case Shapes::triangle:
            this->name = "triangle";
            break;
        case Shapes::square:
            this->name = "square";
            break;
        case Shapes::star:
            this->name = "star";
            break;
        }
    }

    std::string GetName() const
    {
        return name;
    }

    Shapes GetShape() const
    {
        return shape;
    }

    virtual bool operator==(const Form& rso) const
    {
        return shape == rso.shape;
    }

    virtual bool IsEqual(const Form& rso) const
    {
        return *this == rso;
    }

private:
    Shapes shape;
    std::string name;
};

#endif