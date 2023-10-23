#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Character.h>
#include <Enums.h>
#include <Player.h>

class Enemy : public Character {
public:
  // clang-format off
  Enemy(GameObjectType objectType, float maxChaseTime, float chaseCooldownTime) 
    : Character(objectType), _MAX_CHASE_TIME(maxChaseTime), _CHASE_COOLDOWN_TIME(chaseCooldownTime){};
  Enemy(GameObjectType objectType, float maxChaseTime, float chaseCooldownTime, float scale) 
    : Character(objectType, scale), _MAX_CHASE_TIME(maxChaseTime), _CHASE_COOLDOWN_TIME(chaseCooldownTime){};
  Enemy(GameObjectType objectType, float maxChaseTime, float chaseCooldownTime, float scale, float speed) 
    : Character(objectType, scale, speed), _MAX_CHASE_TIME(maxChaseTime), _CHASE_COOLDOWN_TIME(chaseCooldownTime){};
  // clang-format on

  void update(Player* player, float deltaTime);

private:
  void checkPlayerCollision(Player* player);
  void updateChaseCooldown(float deltaTime);
  void updatePlayerChase(Player* player, float deltaTime);

  void resetChaseCooldown();

  const float _MAX_CHASE_TIME;
  const float _CHASE_COOLDOWN_TIME;
  float _currentChaseTime = 0.f;
  float _currentCooldownTime = 0.f;

  bool _isCoolingDownChase = false;
};
