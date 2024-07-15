#ifndef ENEMY_H
#define ENEMY_H

#include <string>


class Player;

class Enemy {

public:
  Enemy(const std::string& name, int health, int attackPower);

  virtual void attack(Player& player) const;
  virtual std::string getInfo() const;
  virtual void takeDamage(int damage);
  int getHealth() const;
  int getAttackPower() const;
  int dropLoot() const;
  std::string getName() const;
  bool isAlive() const;
  virtual ~Enemy();

protected:
  std::string name;
  int health;
  int attackPower;

};

#endif
