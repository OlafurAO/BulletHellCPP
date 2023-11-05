#pragma once

#include <string>

enum ResType { AUDIO_SFX, AUDIO_MUSIC, SPRITE_CHAR, SPRITE_WEAPONS, SPRITE_UI };

class Path {
public:
  Path(const char* src, ResType type) {
    switch (type) {
    case ResType::AUDIO_SFX:
      _path += RESOURCE_SFX;
      break;
    case ResType::AUDIO_MUSIC:
      _path += RESOURCE_MUSIC;
      break;
    case ResType::SPRITE_CHAR:
      _path += RESOURCE_SPRITE_CHARACTER;
      break;
    case ResType::SPRITE_WEAPONS:
      _path += RESOURCE_SPRITE_WEAPON;
      break;
    case ResType::SPRITE_UI:
      _path += RESOURCE_SPRITE_UI;
      break;
    default:
      break;
    }

    _path += src;
  }

  const char* getPath() { return _path.c_str(); }

private:
  const std::string RESOURCE_SFX = "res/sfx/.WAV/";
  const std::string RESOURCE_MUSIC = "res/music/.OGG/";
  const std::string RESOURCE_SPRITE_CHARACTER = "res/sprites/characters/";
  const std::string RESOURCE_SPRITE_WEAPON = "res/sprites/weapons/";
  const std::string RESOURCE_SPRITE_UI = "res/sprites/ui/";

  std::string _path = "";
};
