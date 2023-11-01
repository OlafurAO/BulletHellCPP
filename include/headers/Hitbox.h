#pragma once

#include <glm/glm.hpp>
#include <sdl2/SDL.h>

#include <iostream>

class Hitbox {
public:
  Hitbox(glm::vec3 pos, SDL_FRect dimensions);
  ~Hitbox();

  void updatePosition(glm::vec3 newPos);

  SDL_FRect getHitboxBounds() const;

  float getX();
  float getY();
  float getWidth();
  float getHeight();

  bool operator==(const Hitbox& other) const;

  // For debug purposes
  friend std::ostream& operator<<(std::ostream& out, const Hitbox& hitbox) {
    SDL_FRect bounds = hitbox.getHitboxBounds();
    out << "(X:" << bounds.x << ", Y:" << bounds.y << ", W:" << bounds.w << ", H:" << bounds.h << ")";
    return out;
  };

private:
  glm::vec3 _position;
  SDL_FRect _dimensions;
};
