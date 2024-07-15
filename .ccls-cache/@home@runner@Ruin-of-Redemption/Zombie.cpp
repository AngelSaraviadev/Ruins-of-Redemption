#include "Zombie.h"
#include <iostream>

Zombie::Zombie() : Enemy("Zombie", 70 , 15) {}

void Zombie::attack(Player& player) const {
  std::cout << "Zombie bites you with its teeth for " << getAttackPower() << " damage!" << std::endl;
  Enemy::attack(player);
  
}