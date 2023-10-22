#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sdl2_image/SDL_image.h>

#include <Enums.h>

class Texture2D {
public:
  Texture2D(TextureType texType = TextureType::SPRITE);

  void generateTexture(SDL_Surface* img, SDL_Renderer* renderer, unsigned int width, unsigned int height);
  void generateSpriteSheet(int rows, int cols);

  void cleanUp();

  SDL_Texture* getTexture();
  SDL_Surface* getTextureSurface();
  SDL_Rect getSpriteFrame(unsigned int spriteIndex);

  std::pair<int, int> getFrameSize();

  TextureType getTextureType() const;

private:
  SDL_Texture* _texture;
  SDL_Surface* _textureSurface;
  TextureType _textureType;

  std::vector<SDL_Rect> _spriteFrames;

  int _width, _height;
  int _spriteWidth, _spriteHeight;
  unsigned int _spriteRows, _spriteCols;
};
