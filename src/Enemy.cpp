#include <headers/Enemy.h>

void Enemy::update(Player* player, float deltaTime) { updatePlayerChase(player, deltaTime); }

void Enemy::updatePlayerChase(Player* player, float deltaTime) {
  if (_isCoolingDownChase) {
    _currentCooldownTime += deltaTime;
    if (_currentCooldownTime >= _CHASE_COOLDOWN_TIME) {
      _isCoolingDownChase = false;
      _currentCooldownTime = 0.f;
      _canMove = true;
    }
  } else {
    _currentChaseTime += deltaTime;
    if (_currentChaseTime >= _MAX_CHASE_TIME) {
      _isCoolingDownChase = true;
      _currentChaseTime = 0.f;
      _canMove = false;
    }
  }

  if (!_canMove)
    return;

  glm::vec3 playerPosition = player->getPositionVec();
  float posThreshold = 0.025f;
  if (playerPosition.x < _position.x - posThreshold) {
    setMovementVectorX(-1);
  } else if (playerPosition.x > _position.x + posThreshold) {
    setMovementVectorX(1);
  } else {
    setMovementVectorX(0);
  }

  if (playerPosition.y < _position.y - posThreshold) {
    setMovementVectorY(-1);
  } else if (playerPosition.y > _position.y + posThreshold) {
    setMovementVectorY(1);
  } else {
    setMovementVectorY(0);
  }
}
