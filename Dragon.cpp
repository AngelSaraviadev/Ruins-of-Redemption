#include "Dragon.h"
#include <iostream>

Dragon::Dragon() : Enemy("Dragon", 100, 20) {}

void Dragon::attack(Player& player) const {
  std::cout << "Dragon attacks you with its fire breath for " << getAttackPower() << " damage!" << std::endl;
}