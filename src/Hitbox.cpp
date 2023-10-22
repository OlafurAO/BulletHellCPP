#include "Hitbox.h"

Hitbox::Hitbox(glm::vec3 pos, SDL_FRect dimensions) {
  _dimensions = dimensions;
  _position = pos;
}

Hitbox::~Hitbox() {}

void Hitbox::updatePosition(glm::vec3 newPos) { _position = newPos; }

SDL_FRect Hitbox::getDimensions() { return {_position.x + _dimensions.x, _position.y + _dimensions.y, _dimensions.w, _dimensions.h}; }
