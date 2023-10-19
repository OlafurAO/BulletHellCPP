#pragma once

#include <Character.h>

class Player : public Character {
public:
  Player(GameObjectType objectType) : Character(objectType){};
  Player(GameObjectType objectType, float scale) : Character(objectType, scale){};
  Player(GameObjectType objectType, float scale, float speed) : Character(objectType, scale, speed){};
  ~Player();

  void update();
};
