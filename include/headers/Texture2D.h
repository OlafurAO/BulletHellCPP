#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <Enums.h>

class Texture2D {
public:
  Texture2D(TextureType texType = TextureType::SPRITE);

  void generateTexture(SDL_Surface* img, SDL_Renderer* renderer, unsigned int width, unsigned int height);
  void generateSpriteSheet(int rows, int cols);

  void cleanUp();

  SDL_Texture* getTexture();
  SDL_Rect getSpriteFrame(unsigned int spriteIndex);

  TextureType getTextureType() const;

private:
  SDL_Texture* _texture;
  TextureType _textureType;

  std::vector<SDL_Rect> _spriteFrames;

  unsigned int _width, _height;
  unsigned int _spriteRows, _spriteCols;
};
