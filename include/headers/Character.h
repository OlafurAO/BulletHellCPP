#pragma once

#include <Enums.h>
#include <GameObject.h>

class Character : public GameObject {
public:
  Character(GameObjectType objectType) : GameObject(objectType) {}
  Character(GameObjectType objectType, float scale) : GameObject(objectType, scale){};
  Character(GameObjectType objectType, float scale, float speed) : GameObject(objectType, scale, speed){};

  void update();
  void attack();

  bool isAttacking();

private:
  void updateDirection();
  void updateAnimation();

  void checkAttackAnimation();

  CharacterDirection _characterDirection = CharacterDirection::RIGHT;
  bool _isAttacking = false;
  bool _isMoving = false;
};
