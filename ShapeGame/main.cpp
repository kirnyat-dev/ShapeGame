#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Sceen.h"
#include "GameLevel.h"
#include "LevelBasedWorker.h"
#include "SceenDirector.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));

    std::cout << "Сопоставь предмет\n";
    std::cout << "Выберите уровень сложности:\n";
    std::cout << "1. Лёгкий (1 свойство, 10 очков)\n";
    std::cout << "2. Сложный (2 свойства, 20 очков)\n";
    int choice;
    std::cout << "Выбор: ";
    std::cin >> choice;

    GameLevel level = (choice == 2)
        ? GameLevel("Сложный", 2, 0, 20)
        : GameLevel("Лёгкий", 1, 0, 10);

    Sceen sceen(level);
    LevelBasedWorker worker(level);
    SceenDirector director(&sceen, &worker);
    director.Produce();

    sceen.Start();

    bool quit = false;
    while (!sceen.IsRoundFinished() && !quit)
    {
        std::cout << "\n" << sceen.GetStateString() << "\n\n";

        auto actions = sceen.GetAvailableActions();
        for (size_t i = 0; i < actions.size(); ++i)
        {
            std::cout << i + 1 << ". " << actions[i].description << "\n";
        }
        std::cout << "Выберите действие: ";

        int actionChoice;
        std::cin >> actionChoice;
        if (actionChoice < 1 || actionChoice >(int)actions.size())
        {
            std::cout << "Неверный выбор.\n";
            continue;
        }

        Sceen::PlayerAction action = actions[actionChoice - 1].action;
        int frameIndex = -1;

        if (action == Sceen::PlayerAction::InspectFrame || action == Sceen::PlayerAction::PlaceToy)
        {
            if (sceen.GetPanel().GetFramesCount() == 0)
            {
                std::cout << "Нет отверстий!\n";
                continue;
            }
            std::cout << "Введите индекс отверстия (0.." << sceen.GetPanel().GetFramesCount() - 1 << "): ";
            std::cin >> frameIndex;
        }

        auto result = sceen.PerformAction(action, frameIndex);
        std::cout << result.message << "\n";

        if (action == Sceen::PlayerAction::Quit)
        {
            quit = true;
        }
    }

    std::cout << "\n" << "Игра окончена\n";
    std::cout << "Финальный счёт: " << sceen.GetScore() << "\n";

    return 0;
}