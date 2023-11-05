#include <Character.h>

Character::~Character() { delete _equippedWeapon; }

void Character::update(float deltaTime) {
  if (_animator == nullptr)
    return;

  if (_movementVector != glm::vec2(0.f)) {
    _isMoving = true;
  } else {
    _isMoving = false;
  }

  // TODO: add collision check with projectiles

  updateTakeDamage(deltaTime);

  if (!_isAttacking) {
    updateDirection();
    updateAnimation();
    updateEquippedWeapon();
  } else {
    checkAttackAnimation();
  }
}

void Character::checkProjectileCollision(std::vector<Projectile*> projectiles) {
  // ALKSALAJHDSSDAS
  //  AOISD POIASJOIJASD
}

void Character::updateDirection() {
  glm::vec2 crosshairPos = _crosshair.getPositionVec();
  glm::vec2 center = getHitboxCenterPoint();
  if (crosshairPos.x < center.x) {
    _characterDirection = CharacterDirection::LEFT;
    _direction = -1;
  } else if (crosshairPos.x > center.x) {
    _direction = 1;
    _characterDirection = CharacterDirection::RIGHT;
  }
}

void Character::updateAnimation() {
  AnimationType animationType;
  if (_isMoving) {
    animationType = AnimationType::WALK1;
  } else {
    animationType = AnimationType::IDLE1;
  }
  _animator->playAnimation(animationType);
}

void Character::updateTakeDamage(float deltaTime) {
  if (_isTakingDamage) {
    if (_damageCooldown >= 0) {
      updateDamageCooldown(deltaTime);
    } else {
      _color = g_DEFAULT_COLOR;
      _isTakingDamage = false;
    }
  }
}

void Character::updateEquippedWeapon() {
  if (_equippedWeapon != nullptr) {
    glm::vec2 centerPoint = getHitboxCenterPoint();
    _equippedWeapon->setDirection(_characterDirection == CharacterDirection::RIGHT ? 1 : -1);
    _equippedWeapon->setPosition(glm::vec2(centerPoint.x, centerPoint.y + 10.f));
    _equippedWeapon->followCrosshair(_crosshair.getPositionVec());
  }
}

void Character::updateDamageCooldown(float deltaTime) { _damageCooldown -= deltaTime; }

void Character::checkAttackAnimation() {
  if (!_animator->isPlayingAnimation()) {
    _animator->playAnimation(_animator->getPrevAnimation());
    _isAttacking = false;
  }
}

void Character::attack() {
  if (_isAttacking)
    return;

  // TODO: CHECK IF HAS ATTACK ANIMATION
  _equippedWeapon->fireWeapon(_crosshair.getPositionVec());
  //_isAttacking = true;
  //_animator->playAnimation(AnimationType::ATTACK1);
}

void Character::updateCrosshair(int x, int y) { _crosshair.updatePosition(x, y); }

void Character::takeDamage(int damage) {
  _audioManager->playSfx(_objectType == GameObjectType::PLAYER ? SFX::DAMAGE_PLAYER_01 : SFX::DAMAGE_ENEMY_01);
  _damageCooldown = g_DAMAGE_COOLDOWN;
  _isTakingDamage = true;
  _damage -= damage;
  _color = g_RED;
}

void Character::equipWeapon(Weapon* weapon) { _equippedWeapon = weapon; }

Weapon* Character::getEquippedWeapon() { return _equippedWeapon; }

SDL_Rect Character::getCrosshairPosition() {
  glm::vec2 pos = _crosshair.getPositionVec();
  return {int(pos.x) - 5, int(pos.y) - 5, 10, 10};
}

int Character::getHealth() { return _health; }

bool Character::isAttacking() { return _isAttacking; }

bool Character::isTakingDamage() { return _isTakingDamage; }

bool Character::isColliding(Hitbox* otherHitbox) { return *_hitbox == *otherHitbox; }
