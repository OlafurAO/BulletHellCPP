#include <headers/Character.h>

void Character::update() {
  if (_animator == nullptr) {
    return;
  }

  if (!_isAttacking) {
    updateDirection();
    updateAnimation();
  } else {
    checkAttackAnimation();
  }

  // TODO: when attacking, turning around at the last second won't play the walk animation
  // MOVE ANIMATIONS TO A NEW CHECKER
}

void Character::updateDirection() {
  if (_movementVector != glm::vec3(0.f)) {
    _isMoving = true;
    if (_movementVector.x == 0) {
      // clang-format off
      _characterDirection = 
        (_movementVector.y > 0) ? CharacterDirection::DOWN
          : (_movementVector.y < 0 && _direction < 0) ? CharacterDirection::LEFT
            : (_movementVector.y < 0) ? CharacterDirection::RIGHT
          : _characterDirection;
      // clang-format on      
    } else {
      _characterDirection = CharacterDirection::UP;
    }
  } else {
    _isMoving = false;
  }
}

void Character::updateAnimation() {    
  AnimationType animationType;
  // clang-format off
  if (_isMoving) {    
    animationType =
      _characterDirection == CharacterDirection::DOWN ? AnimationType::WALK1
      : _characterDirection == CharacterDirection::LEFT
        || _characterDirection == CharacterDirection::RIGHT ? AnimationType::WALK3
      : AnimationType::WALK2;
  } else {
    animationType =
      _characterDirection == CharacterDirection::DOWN ? AnimationType::IDLE1
      : _characterDirection == CharacterDirection::LEFT
        || _characterDirection == CharacterDirection::RIGHT ? AnimationType::IDLE3
      : AnimationType::IDLE2; 
  }
  // clang-format on
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

  // clang-format off
  AnimationType attackAnimation = 
    _characterDirection == CharacterDirection::DOWN ? AnimationType::ATTACK1
    : _characterDirection == CharacterDirection::LEFT
      || _characterDirection == CharacterDirection::RIGHT ? AnimationType::ATTACK3
    : AnimationType::ATTACK2;
  // clang-format on
  _animator->playAnimation(attackAnimation);
}

bool Character::isAttacking() { return _isAttacking; }
