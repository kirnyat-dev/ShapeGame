#ifndef _SCEEN_H_
#define _SCEEN_H_

#include "Frames.h"
#include "Toys.h"

class Player;
class Panel;

class Sceen {
public:
	struct Action {

	};

	Sceen() = default;
	Sceen(...);

	void Start();

	void GameCicle();

	Player& GetPlayer();
	Panel& GetPanel();

private:
	Player player;
	Panel panel;
};

#endif	//!_SCEEN_H_