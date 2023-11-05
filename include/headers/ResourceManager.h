#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <sdl2_image/SDL_image.h>

#include <Enums.h>
#include <Path.h>
#include <Texture2D.h>

class ResourceManager {
public:
  ResourceManager();

  void cleanUpResources();
  void setRenderer(SDL_Renderer* renderer);

  Texture2D& loadTexture(Path texFilePath, std::string texKey, TextureType texType, int spriteRows = 0, int spriteCols = 0);
  Texture2D& getTexture(std::string texName);

  SDL_Renderer* getRenderer();

private:
  Texture2D loadTextureFromFile(const char* file, TextureType texType, int spriteRows = 0, int spriteCols = 0);

  SDL_Renderer* _renderer;
  std::map<std::string, Texture2D> _textures;
};
