#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy {
public:
  Goblin();
  void attack(Player& player) const override;
};

#endif
