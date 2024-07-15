#include "Enemy.h"
#include "Player.h"

#include <iostream>

Enemy::Enemy(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower) {}

void Enemy::attack(Player& player) const {
    std::cout << name << " attacks you for " << attackPower << " damage!\n";
    player.takeDamage(attackPower);
}
std::string Enemy::getInfo() const {
  return "Name: " + name + ", Health: " + std::to_string(health) + ", Attack Power: " + std::to_string(attackPower);
}
bool Enemy::isAlive() const {
  return health > 0;
}
std::string Enemy::getName() const {
  return name;
}
int Enemy::getHealth() const{
  return health;
}
int Enemy::getAttackPower() const {
  return attackPower;
}
void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}
int Enemy::dropLoot() const {
    // 50% chance for loot drop
    if (rand() % 2 == 0) {
        // Randomly generate healing amount between 10 and 30
        return rand() % 21 + 10;
    } else {
        // No loot drop
        return 0;
    }
}
Enemy::~Enemy(){
  
}