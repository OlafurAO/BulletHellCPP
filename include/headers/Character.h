#pragma once

#include <sdl2/SDL.h>

#include <Enums.h>
#include <GameObject.h>
#include <Item.h>
#include <Weapon.h>

class Character : public GameObject {
public:
  Character(GameObjectType objectType) : GameObject(objectType) {}
  Character(GameObjectType objectType, float scale) : GameObject(objectType, scale){};
  Character(GameObjectType objectType, float scale, float speed) : GameObject(objectType, scale, speed){};

  void update();
  void attack();

  void equipWeapon(Weapon* weapon);

  GameObject* getEquippedWeapon();

  int getHealth();

  bool isAttacking();

private:
  void updateDirection();
  void updateAnimation();

  void checkAttackAnimation();

  Weapon* _equippedWeapon = nullptr;

  int _health = 10;
  int _damage = 1;

  CharacterDirection _characterDirection = CharacterDirection::RIGHT;
  bool _isAttacking = false;
  bool _isMoving = false;
};
