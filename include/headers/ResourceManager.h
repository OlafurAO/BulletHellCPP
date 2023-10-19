#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <sdl2_image/SDL_image.h>

#include <Enums.h>
#include <Texture2D.h>

class ResourceManager {
public:
  ResourceManager();

  static void cleanUpResources();

  static Texture2D loadTexture(SDL_Renderer* renderer, const char* texFile, std::string texKey, TextureType texType, int spriteRows = 0,
                               int spriteCols = 0);
  static Texture2D& getTexture(std::string texName);

private:
  static Texture2D loadTextureFromFile(SDL_Renderer* renderer, const char* file, TextureType texType, int spriteRows = 0,
                                       int spriteCols = 0);
  static std::map<std::string, Texture2D> _textures;
};
