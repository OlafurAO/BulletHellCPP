#include <GameObject.h>

GameObject::GameObject(GameObjectType objectType) { init(objectType); }

GameObject::GameObject(GameObjectType objectType, float scale) {
  initScale(scale);
  init(objectType);
}

GameObject::GameObject(GameObjectType objectType, float scale, float speed) {
  initScale(scale);
  init(objectType);
  initSpeed(speed);
}

GameObject::~GameObject() { delete _hitbox; }

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

void GameObject::initHitbox(SDL_Renderer* renderer, Texture2D& tex, unsigned int referenceFrameIndex) {
  SDL_Rect srcRect = tex.getSpriteFrame(referenceFrameIndex);
  SDL_FRect destRect = getPositionRect();
  _texFrameSize = tex.getFrameSize();

  SDL_Texture* spritesheet = tex.getTexture();
  SDL_Surface* spriteSurface = tex.getTextureSurface();
  SDL_RenderCopyF(renderer, spritesheet, &srcRect, &destRect);

  if (SDL_LockSurface(spriteSurface) == 0) {
    Uint32* pixels = static_cast<Uint32*>(spriteSurface->pixels);
    int pitch = spriteSurface->pitch / sizeof(Uint32);

    int left = spriteSurface->w;
    int right = 0;
    int top = spriteSurface->h;
    int bottom = 0;

    for (int x = 0; x < srcRect.w; x++) {
      for (int y = 0; y < srcRect.h; y++) {
        Uint32 pixel = pixels[y * pitch + x];
        Uint8 alpha = (pixel & 0xFF000000) >> 24;

        if (alpha != 0) {
          left = std::min(left, x);
          right = std::max(right, x);
          top = std::min(top, y);
          bottom = std::max(bottom, y);
        }
      }
    }

    float multiplier = (g_BASE_SPRITE_SIZE * _scale.x) / _texFrameSize.first;
    SDL_FRect hitboxRect = {left * multiplier, top * multiplier, (right - left + 1) * multiplier, (bottom - top + 1) * multiplier};
    _hitbox = new Hitbox(_position, hitboxRect);

    SDL_UnlockSurface(spriteSurface);
  }

  tex.destroyTextureSurface();
}

void GameObject::updateHitboxPos(glm::vec3 newPos) { _hitbox->updatePosition(newPos); }

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
    updateHitboxPos(_position);
  }
}

void GameObject::setMovementVectorX(int direction) {
  if (_movementVector.x != direction) {
    _movementVector = glm::vec3(1.f * direction, _movementVector.y, 0.f);
    updateDirectionOnMoveX(direction);
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

void GameObject::updateDirectionOnMoveX(int direction) {
  if (direction > 0) {
    _direction = 1;
  } else if (direction < 0) {
    _direction = -1.f;
  }
}

void GameObject::registerTexture(const char* texKey, Texture2D& tex, SDL_Renderer* renderer, unsigned int referenceFrameIndex) {
  initHitbox(renderer, tex, referenceFrameIndex);
  _textureKey = texKey;
}

void GameObject::registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop) {
  _animator->registerAnimation(type, spriteIndices, frameCount, loop);
}

void GameObject::playAnimation(AnimationType type) { _animator->playAnimation(type); }

void GameObject::setCanMove(bool canMove) { _canMove = canMove; }

void GameObject::setPosition(glm::vec3 newPos) {
  _position = newPos;
  updateHitboxPos(newPos);
}

Hitbox* GameObject::getHitbox() { return _hitbox; }

SDL_FRect GameObject::getHitboxBounds() { return _hitbox->getHitboxBounds(); }

SDL_Color GameObject::getColor() { return _color; }

SDL_FRect GameObject::getPositionRect() {
  // clang-format off
  SDL_FRect rect = {
    _position.x,
    _position.y,
    g_BASE_SPRITE_SIZE * _scale.x,
    g_BASE_SPRITE_SIZE * _scale.y,
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
