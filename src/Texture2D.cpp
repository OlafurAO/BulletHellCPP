#include <Texture2D.h>

Texture2D::Texture2D(TextureType texType) : _width(0), _height(0), _textureType(texType){};

void Texture2D::generateTexture(SDL_Surface* img, SDL_Renderer* renderer, unsigned int width, unsigned int height) {
  _texture = SDL_CreateTextureFromSurface(renderer, img);
  _width = width;
  _height = height;
}

void Texture2D::generateSpriteSheet(int rows, int cols) {
  _spriteRows = rows;
  _spriteCols = cols;

  int spriteWidth = _width / cols;
  int spriteHeight = _height / rows;

  for (int i = 0; i < rows; i++) {
    for (int k = 0; k < cols; k++) {
      _spriteFrames.push_back({k * spriteWidth, i * spriteHeight, spriteWidth, spriteHeight});
    }
  }
}

void Texture2D::cleanUp() { SDL_DestroyTexture(_texture); }

SDL_Texture* Texture2D::getTexture() { return _texture; }

SDL_Rect Texture2D::getSpriteFrame(unsigned int spriteIndex) {
  if (spriteIndex < _spriteFrames.size()) {
    return _spriteFrames[spriteIndex];
  }

  return {};
}

TextureType Texture2D::getTextureType() const { return _textureType; }
