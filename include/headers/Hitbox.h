#pragma once

#include <glm/glm.hpp>
#include <sdl2/SDL.h>

class Hitbox {
public:
  Hitbox(glm::vec3 pos, SDL_FRect dimensions);
  ~Hitbox();

  void updatePosition(glm::vec3 newPos);

  SDL_FRect getDimensions();

private:
  glm::vec3 _position;
  SDL_FRect _dimensions;
};
