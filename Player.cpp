#include "Player.h"
#include <iostream>

using namespace std;

Player::Player() : health(100) {}

int Player::attack() const {
  // random attack power between 5 and 20
  int attackPower = rand() % 16 + 5;
  cout << "You attack the enemy for " << attackPower << " damage!" << endl;
  return attackPower;
}

void Player::takeDamage(int damage){
  health -= damage;
  cout << "You take " << damage << " damage. Your health is now " << health << "." << endl;
}

void Player::heal(int amount){
  health += amount;
  cout << "You heal for " << amount << " health. Your health is now " << health << "." << endl;
  
}
void Player::setTokens(int tokens){
  credits = tokens;
}

void Player::setHealth(int newHealth){
  health = newHealth;
}
void Player::addTokens(int amount) {
    credits += amount;
}
int Player::getTokens() const {
    return credits;
}
bool Player::isAlive() const {
  return health > 0;
}

int Player::getHealth() const{
  return health;
}