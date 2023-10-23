#include <Texture2D.h>

Texture2D::Texture2D(TextureType texType) : _width(0), _height(0), _textureType(texType){};

void Texture2D::generateTexture(SDL_Surface* img, SDL_Renderer* renderer, unsigned int width, unsigned int height) {
  _textureSurface = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, 0);
  _texture = SDL_CreateTextureFromSurface(renderer, _textureSurface);

  _width = width;
  _height = height;
}

void Texture2D::generateSpriteSheet(int rows, int cols) {
  _spriteRows = rows;
  _spriteCols = cols;

  _spriteWidth = _width / cols;
  _spriteHeight = _height / rows;

  for (int i = 0; i < rows; i++) {
    for (int k = 0; k < cols; k++) {
      _spriteFrames.push_back({k * _spriteWidth, i * _spriteHeight, _spriteWidth, _spriteHeight});
    }
  }
}

void Texture2D::cleanUp() { SDL_DestroyTexture(_texture); }

void Texture2D::destroyTextureSurface() { SDL_FreeSurface(_textureSurface); }

SDL_Texture* Texture2D::getTexture() { return _texture; }

SDL_Surface* Texture2D::getTextureSurface() { return _textureSurface; }

SDL_Rect Texture2D::getSpriteFrame(unsigned int spriteIndex) {
  if (spriteIndex < _spriteFrames.size()) {
    return _spriteFrames[spriteIndex];
  }

  return {};
}

std::pair<int, int> Texture2D::getFrameSize() { return std::pair<int, int>(_spriteWidth, _spriteHeight); }

TextureType Texture2D::getTextureType() const { return _textureType; }
