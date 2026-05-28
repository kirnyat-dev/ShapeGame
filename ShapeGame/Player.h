#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <memory>
#include "Toys.h"

class Player
{
public:
    void AddToy(std::unique_ptr<Toys> toy)
    {
        toys.push_back(std::move(toy));
    }

    bool HasToys() const
    {
        return !toys.empty();
    }

    const Toys& GetCurrentToy() const
    {
        return *toys[currentIndex];
    }

    void RemoveCurrentToy()
    {
        if (currentIndex < toys.size())
        {
            toys.erase(toys.begin() + currentIndex);
        }
        if (currentIndex >= toys.size() && currentIndex > 0)
        {
            currentIndex = toys.size() - 1;
        }
    }

    void SelectNextToy()
    {
        if (!toys.empty())
        {
            currentIndex = (currentIndex + 1) % toys.size();
        }
    }

    void SelectPreviousToy()
    {
        if (!toys.empty())
        {
            currentIndex = (currentIndex - 1 + toys.size()) % toys.size();
        }
    }

    int GetToysCount() const
    {
        return static_cast<int>(toys.size());
    }

private:
    std::vector<std::unique_ptr<Toys>> toys;
    size_t currentIndex = 0;
};

#endif