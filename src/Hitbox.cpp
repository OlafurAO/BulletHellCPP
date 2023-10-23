#include "Hitbox.h"

Hitbox::Hitbox(glm::vec3 pos, SDL_FRect dimensions) {
  _dimensions = dimensions;
  _position = pos;
}

Hitbox::~Hitbox() {}

void Hitbox::updatePosition(glm::vec3 newPos) { _position = newPos; }

SDL_FRect Hitbox::getHitboxBounds() const {
  return {_position.x + _dimensions.x, _position.y + _dimensions.y, _dimensions.w, _dimensions.h};
}

bool Hitbox::operator==(const Hitbox& other) const {
  SDL_FRect thisBounds = this->getHitboxBounds();
  SDL_FRect otherBounds = other.getHitboxBounds();

  return std::max(thisBounds.x, otherBounds.x) < std::min(thisBounds.x + thisBounds.w, otherBounds.x + otherBounds.w) &&
         std::max(thisBounds.y, otherBounds.y) < std::min(thisBounds.y + thisBounds.h, otherBounds.y + otherBounds.h);
}
