#ifndef _SCEEN_H_
#define _SCEEN_H_

#include "Player.h"
#include "Panel.h"
#include "GameLevel.h"
#include <vector>
#include <string>

class Sceen
{
public:
    enum class PlayerAction
    {
        InspectToy,
        InspectFrame,
        PlaceToy,
        NextToy,
        PrevToy,
        Quit
    };

    struct ActionResult
    {
        bool success;
        int pointsEarned;
        std::string message;
    };

    explicit Sceen(const GameLevel& level);

    void Start();
    bool IsRoundFinished() const;

    int GetScore() const { return score; }

    struct ActionInfo
    {
        PlayerAction action;
        std::string description;
    };
    std::vector<ActionInfo> GetAvailableActions() const;

    ActionResult PerformAction(PlayerAction action, int frameIndex = -1);

    std::string GetStateString() const;

    const Panel& GetPanel() const { return panel; }

private:
    Player player;
    Panel panel;
    GameLevel level;
    int score = 0;
    bool isGameActive = false;

    void GenerateLevelContent();
};

#endif