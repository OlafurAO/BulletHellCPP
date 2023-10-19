#include <headers/GameObject.h>

GameObject::GameObject(GameObjectType objectType) { init(objectType); }

GameObject::GameObject(GameObjectType objectType, float scale) {
  init(objectType);
  initScale(scale);
}

GameObject::GameObject(GameObjectType objectType, float scale, float speed) {
  init(objectType);
  initScale(scale);
  initSpeed(speed);
}

GameObject::~GameObject() {}

void GameObject::init(GameObjectType objectType) {
  _animator = nullptr;
  _objectType = objectType;
  _canMove = true;

  _movementVector = glm::vec3(0.f);
  _position = glm::vec3(0.f);
}

void GameObject::initScale(float scale) { _scale = glm::vec3(scale); }

void GameObject::initSpeed(float speed) { _speed = speed; }

void GameObject::initAnimator() { _animator = new Animator(); }

void GameObject::update(double deltaTime) {
  updatePrevMovementVector();
  updateMovement(deltaTime);

  if (_animator != nullptr) {
    _animator->update(deltaTime);
  }
}

void GameObject::updateMovement(double deltaTime) {
  if (_canMove && _movementVector != glm::vec3(0.f)) {
    _position += glm::normalize(_movementVector) * _speed * (float)deltaTime;
  }
}

void GameObject::setMovementVectorX(int direction) {
  if (_movementVector.x != direction) {
    _movementVector = glm::vec3(1.f * direction, _movementVector.y, 0.f);
    updateRotationOnMoveX(direction);
  }
}

void GameObject::setMovementVectorY(int direction) {
  if (_movementVector.y != direction) {
    _movementVector = glm::vec3(_movementVector.x, 1.f * direction, 0.f);
  }
}

void GameObject::updatePrevMovementVector() {
  if (_movementVector != glm::vec3(0.f) && _prevMovementVector != _movementVector) {
    _prevMovementVector = _movementVector;
  }
}

void GameObject::updateRotationOnMoveX(int direction) {
  if (direction > 0) {
    _direction = 1;
  } else if (direction < 0) {
    _direction = -1.f;
  }
}

void GameObject::registerTextureKey(const char* texKey) { _textureKey = texKey; }

void GameObject::registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop) {
  _animator->registerAnimation(type, spriteIndices, frameCount, loop);
}

void GameObject::playAnimation(AnimationType type) { _animator->playAnimation(type); }

void GameObject::setCanMove(bool canMove) { _canMove = canMove; }

SDL_Rect GameObject::getPositionRect() {
  // clang-format off
  SDL_Rect rect = {
    static_cast<int>(_position.x), 
    static_cast<int>(_position.y), 
    int(g_baseSpriteSize * _scale.x),
    int(g_baseSpriteSize * _scale.y)
  };
  // clang-format on

  return rect;
}

glm::vec3 GameObject::getPositionVec() { return _position; }

int GameObject::getDirection() { return _direction; }

GameObjectType GameObject::getObjectType() { return _objectType; }

const char* GameObject::getTextureKey() { return _textureKey; }

unsigned int GameObject::getSpriteIndex() {
  if (_animator != nullptr) {
    return _animator->getCurrentSpriteIndex();
  }

  return 0;
}

int GameObject::getHealth() { return _health; }
