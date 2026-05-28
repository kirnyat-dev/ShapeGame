#include "Sceen.h"
#include "ShapeProperty.h"
#include "ColorProperty.h"
#include <random>

Sceen::Sceen(const GameLevel& level) : level(level) {}

void Sceen::Start()
{
    GenerateLevelContent();
    isGameActive = true;
    score = 0;
}

bool Sceen::IsRoundFinished() const
{
    return !isGameActive || !player.HasToys() || panel.GetFramesCount() == 0;
}

std::vector<Sceen::ActionInfo> Sceen::GetAvailableActions() const
{
    std::vector<ActionInfo> actions;
    actions.push_back({ PlayerAction::InspectToy, "Осмотреть текущую игрушку" });
    actions.push_back({ PlayerAction::InspectFrame, "Осмотреть отверстие (нужен индекс)" });
    actions.push_back({ PlayerAction::PlaceToy, "Поместить игрушку в отверстие (нужен индекс)" });
    actions.push_back({ PlayerAction::NextToy, "Следующая игрушка" });
    actions.push_back({ PlayerAction::PrevToy, "Предыдущая игрушка" });
    actions.push_back({ PlayerAction::Quit, "Выйти из игры" });
    return actions;
}

Sceen::ActionResult Sceen::PerformAction(PlayerAction action, int frameIndex)
{
    if (!isGameActive)
    {
        return { false, 0, "Игра окончена" };
    }

    switch (action)
    {
    case PlayerAction::InspectToy:
    {
        if (!player.HasToys())
        {
            return { false, 0, "Нет игрушек" };
        }
        std::string desc = player.GetCurrentToy().getProperties().getDescription();
        return { true, 0, "Игрушка имеет свойства: " + desc };
    }

    case PlayerAction::InspectFrame:
    {
        if (frameIndex < 0 || frameIndex >= panel.GetFramesCount())
        {
            return { false, 0, "Неверный индекс отверстия" };
        }
        std::string desc = panel.GetFrame(frameIndex).getProperties().getDescription();
        return { true, 0, "Отверстие требует свойства: " + desc };
    }

    case PlayerAction::PlaceToy:
    {
        if (!player.HasToys())
        {
            return { false, 0, "Нет игрушек" };
        }
        if (frameIndex < 0 || frameIndex >= panel.GetFramesCount())
        {
            return { false, 0, "Неверный индекс отверстия" };
        }
        if (panel.TryPlaceToy(player.GetCurrentToy(), frameIndex, level.propertiesCount))
        {
            player.RemoveCurrentToy();
            int points = level.pointsPerSuccess;
            score += points;
            return { true, points, "Успех! +" + std::to_string(points) + " очков" };
        }
        else
        {
            return { false, 0, "Игрушка не подходит" };
        }
    }

    case PlayerAction::NextToy:
    {
        player.SelectNextToy();
        return { true, 0, "Выбрана следующая игрушка" };
    }

    case PlayerAction::PrevToy:
    {
        player.SelectPreviousToy();
        return { true, 0, "Выбрана предыдущая игрушка" };
    }

    case PlayerAction::Quit:
    {
        isGameActive = false;
        return { true, 0, "Игра завершена" };
    }
    }
    return { false, 0, "Неизвестное действие" };
}

std::string Sceen::GetStateString() const
{
    return "Счёт: " + std::to_string(score) +
        " | Игрушек: " + std::to_string(player.GetToysCount()) +
        " | Отверстий: " + std::to_string(panel.GetFramesCount());
}

void Sceen::GenerateLevelContent()
{
    std::vector<Form::Shapes> allShapes = {
        Form::Shapes::circle,
        Form::Shapes::triangle,
        Form::Shapes::square,
        Form::Shapes::star
    };

    std::vector<ColorProperty::Color> allColors = {
        ColorProperty::Color::Red,
        ColorProperty::Color::Green,
        ColorProperty::Color::Blue,
        ColorProperty::Color::Yellow
    };

    int numPairs = 4;

    for (int i = 0; i < numPairs; ++i)
    {
        auto toyProps = std::make_unique<ItemProperties>();
        auto frameProps = std::make_unique<ItemProperties>();

        int shapeIndex = rand() % allShapes.size();
        Form shapeForm(allShapes[shapeIndex]);
        toyProps->addProperty(std::make_unique<ShapeProperty>(shapeForm));
        frameProps->addProperty(std::make_unique<ShapeProperty>(shapeForm));

        if (level.propertiesCount >= 2)
        {
            int toyColorIndex = rand() % allColors.size();
            int frameColorIndex = rand() % allColors.size();
            toyProps->addProperty(std::make_unique<ColorProperty>(allColors[toyColorIndex]));
            frameProps->addProperty(std::make_unique<ColorProperty>(allColors[frameColorIndex]));
        }

        player.AddToy(std::make_unique<Toys>(std::move(toyProps)));
        panel.AddFrame(std::make_unique<Frames>(std::move(frameProps)));
    }
}