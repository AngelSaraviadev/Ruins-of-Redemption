#include "Goblin.h"
#include "Enemy.h"
#include <iostream>
#include "Player.h"


Goblin::Goblin() : Enemy("Goblin", 50, 10) {}

void Goblin::attack(Player& player) const {
  std::cout << "Goblin attacks you with its club for " << getAttackPower() << " damage!" << std::endl;
  Enemy::attack(player);
}
