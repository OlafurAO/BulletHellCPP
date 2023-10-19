#include <ResourceManager.h>

std::map<std::string, Texture2D> ResourceManager::_textures;

ResourceManager::ResourceManager() {}

void ResourceManager::cleanUpResources() {
  for (auto& tex : _textures) {
    tex.second.cleanUp();
  }
}

Texture2D ResourceManager::loadTexture(SDL_Renderer* renderer, const char* texFile, std::string texKey, TextureType texType, int spriteRows,
                                       int spriteCols) {
  _textures[texKey] = loadTextureFromFile(renderer, texFile, texType, spriteRows, spriteCols);
  return _textures[texKey];
}

Texture2D& ResourceManager::getTexture(std::string texName) { return _textures[texName]; }

Texture2D ResourceManager::loadTextureFromFile(SDL_Renderer* renderer, const char* texFile, TextureType texType, int spriteRows,
                                               int spriteCols) {
  Texture2D texture = Texture2D(texType);

  SDL_Surface* img = IMG_Load(texFile);
  texture.generateTexture(img, renderer, img->w, img->h);

  if (texType == TextureType::SPRITESHEET) {
    texture.generateSpriteSheet(spriteRows, spriteCols);
  }

  SDL_FreeSurface(img);
  return texture;
}
