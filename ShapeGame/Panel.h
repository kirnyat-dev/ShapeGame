#ifndef _PANEL_H_
#define _PANEL_H_

#include <vector>
#include <memory>
#include "Frames.h"

class Panel
{
public:
    void AddFrame(std::unique_ptr<Frames> frame)
    {
        frames.push_back(std::move(frame));
    }

    bool TryPlaceToy(const Toys& toy, int frameIndex, int propertiesCount)
    {
        if (frameIndex >= 0 && frameIndex < static_cast<int>(frames.size()))
        {
            if (frames[frameIndex]->IsPassable(toy, propertiesCount))
            {
                frames.erase(frames.begin() + frameIndex);
                return true;
            }
        }
        return false;
    }

    int GetFramesCount() const
    {
        return static_cast<int>(frames.size());
    }

    const Frames& GetFrame(int index) const
    {
        return *frames[index];
    }

private:
    std::vector<std::unique_ptr<Frames>> frames;
};

#endif