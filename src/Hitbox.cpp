#include <Hitbox.h>

Hitbox::Hitbox(glm::vec2 pos, SDL_FRect dimensions) {
  _dimensions = dimensions;
  _position = pos;
}

Hitbox::~Hitbox() {}

void Hitbox::updatePosition(glm::vec2 newPos) { _position = newPos; }

SDL_FRect Hitbox::getHitboxBounds() const {
  return {_position.x + _dimensions.x, _position.y + _dimensions.y, _dimensions.w, _dimensions.h};
}

float Hitbox::getX() { return _position.x + _dimensions.x; }

float Hitbox::getY() { return _position.y + _dimensions.y; }

float Hitbox::getWidth() { return _dimensions.w; }

float Hitbox::getHeight() { return _dimensions.h; }

bool Hitbox::operator==(const Hitbox& other) const {
  SDL_FRect thisBounds = this->getHitboxBounds();
  SDL_FRect otherBounds = other.getHitboxBounds();

  return std::max(thisBounds.x, otherBounds.x) < std::min(thisBounds.x + thisBounds.w, otherBounds.x + otherBounds.w) &&
         std::max(thisBounds.y, otherBounds.y) < std::min(thisBounds.y + thisBounds.h, otherBounds.y + otherBounds.h);
}
