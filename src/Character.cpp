#include <Character.h>
#include <headers/Character.h>

void Character::update() {
  if (_animator == nullptr) {
    return;
  }

  if (!_isAttacking) {
    updateDirection();
    updateAnimation();

    if (_equippedWeapon != nullptr) {
      _equippedWeapon->setDirection(_characterDirection == CharacterDirection::RIGHT ? 1 : -1);
      _equippedWeapon->setPosition(_position - glm::vec3(10.f, -20.f, 0.f) + ((g_baseSpriteSize * _scale.x) / 2));
    }
  } else {
    checkAttackAnimation();
  }

  // TODO: when attacking, turning around at the last second won't play the walk animation
  // MOVE ANIMATIONS TO A NEW CHECKER
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

void Character::equipWeapon(Weapon* weapon) { _equippedWeapon = weapon; }

GameObject* Character::getEquippedWeapon() { return _equippedWeapon; }

int Character::getHealth() { return _health; }

bool Character::isAttacking() { return _isAttacking; }
