#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <ctime>

class Player {
public:
  Player();

  int attack() const;
  void takeDamage(int damage);
  bool isAlive() const;
  void heal(int amount);
  void setHealth(int health);
  void setTokens(int tokens);
  void addTokens(int amount);
  int getHealth() const; //retreive the players health
  int getTokens() const;
private:
  int health;
  int credits;
};
#endif