#include <Character.h>
#include <headers/Character.h>

void Character::update(float deltaTime) {
  if (_animator == nullptr) {
    return;
  }

  updateTakeDamage(deltaTime);

  if (!_isAttacking) {
    updateDirection();
    updateAnimation();
    updateEquippedWeapon();
  } else {
    checkAttackAnimation();
  }
}

void Character::updateDirection() {
  if (_movementVector != glm::vec3(0.f)) {
    _isMoving = true;
    if (_movementVector.x > 0) {
      _characterDirection = CharacterDirection::RIGHT;
    } else if (_movementVector.x < 0) {
      _characterDirection = CharacterDirection::LEFT;
    }
  } else {
    _isMoving = false;
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
    _equippedWeapon->setDirection(_characterDirection == CharacterDirection::RIGHT ? 1 : -1);
    _equippedWeapon->setPosition(_position - glm::vec3(10.f, -20.f, 0.f) + ((g_BASE_SPRITE_SIZE * _scale.x) / 2));
  }
}

void Character::updateDamageCooldown(float deltaTime) { _damageCooldown -= deltaTime; }

void Character::checkAttackAnimation() {
  if (!_animator->isPlayingAnimation()) {
    _animator->playAnimation(_animator->getPrevAnimation());
    setCanMove(true);
    _isAttacking = false;
  }
}

void Character::attack() {
  if (_isAttacking)
    return;

  setCanMove(false);
  _isAttacking = true;
  _animator->playAnimation(AnimationType::ATTACK1);
}

void Character::takeDamage(int damage) {
  _damageCooldown = g_DAMAGE_COOLDOWN;
  _isTakingDamage = true;
  _damage -= damage;
  _color = g_RED;
}

void Character::equipWeapon(Weapon* weapon) { _equippedWeapon = weapon; }

GameObject* Character::getEquippedWeapon() { return _equippedWeapon; }

int Character::getHealth() { return _health; }

bool Character::isAttacking() { return _isAttacking; }

bool Character::isTakingDamage() { return _isTakingDamage; }

bool Character::isColliding(Hitbox* otherHitbox) { return *_hitbox == *otherHitbox; }
