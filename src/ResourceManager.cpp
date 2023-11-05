#include <ResourceManager.h>

ResourceManager::ResourceManager() {}

void ResourceManager::cleanUpResources() {
  for (auto& tex : _textures) {
    tex.second.cleanUp();
  }
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }

Texture2D& ResourceManager::loadTexture(Path texFilePath, std::string texKey, TextureType texType, int spriteRows, int spriteCols) {
  _textures[texKey] = loadTextureFromFile(texFilePath.getPath(), texType, spriteRows, spriteCols);
  return _textures[texKey];
}

Texture2D ResourceManager::loadTextureFromFile(const char* texFile, TextureType texType, int spriteRows, int spriteCols) {
  Texture2D texture = Texture2D(texType);

  SDL_Surface* img = IMG_Load(texFile);
  texture.generateTexture(img, _renderer, img->w, img->h);

  if (texType == TextureType::SPRITESHEET) {
    texture.generateSpriteSheet(spriteRows, spriteCols);
  }

  SDL_FreeSurface(img);
  return texture;
}

Texture2D& ResourceManager::getTexture(std::string texName) { return _textures[texName]; }

SDL_Renderer* ResourceManager::getRenderer() { return _renderer; }
