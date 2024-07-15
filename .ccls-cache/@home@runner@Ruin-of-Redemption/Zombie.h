#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Enemy.h"

class Zombie : public Enemy {
public:
  Zombie();
  void attack(Player& player) const override;
};

#endif