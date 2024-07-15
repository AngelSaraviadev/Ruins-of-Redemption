#ifndef DRAGON_H
#define DRAGON_H

#include "Enemy.h"

class Dragon : public Enemy {
public:
  Dragon();
  void attack(Player& player) const override;
};

#endif