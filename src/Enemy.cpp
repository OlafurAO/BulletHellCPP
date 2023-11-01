#include <Enemy.h>

void Enemy::update(Player* player, float deltaTime) {
  checkPlayerCollision(player);
  updateChaseCooldown(deltaTime);
  updatePlayerChase(player, deltaTime);
}

void Enemy::checkPlayerCollision(Player* player) {
  // TODO: Ignore if enemy attack method involves it avoiding the player
  // TODO: Ignore if enemy is outside of a certain range

  if (!player->isTakingDamage() && isColliding(player->getHitbox())) {
    player->takeDamage(_damage);
    resetChaseCooldown();
  }
}

void Enemy::updateChaseCooldown(float deltaTime) {
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
      resetChaseCooldown();
    }
  }
}

void Enemy::updatePlayerChase(Player* player, float deltaTime) {
  if (!_canMove)
    return;

  glm::vec2 playerCenter = player->getHitboxCenterPoint();
  glm::vec2 enemyCenter = this->getHitboxCenterPoint();
  glm::vec2 direction = glm::normalize(playerCenter - enemyCenter);

  int directionX = (playerCenter.x > enemyCenter.x) ? 1 : (playerCenter.x < enemyCenter.x) ? -1 : 0;
  int directionY = (playerCenter.y > enemyCenter.y) ? 1 : (playerCenter.y < enemyCenter.y) ? -1 : 0;
  setMovementVectorX(directionX);
  setMovementVectorY(directionY);
  updateCrosshair(playerCenter.x, playerCenter.y);
}

void Enemy::resetChaseCooldown() {
  _isCoolingDownChase = true;
  _currentChaseTime = 0.f;
  _canMove = false;
}
