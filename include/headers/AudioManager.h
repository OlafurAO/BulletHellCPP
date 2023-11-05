#pragma once

#include <unordered_map>

#include <sdl2/SDL.h>
#include <sdl2_mixer/SDL_mixer.h>

enum SFX { DAMAGE_PLAYER_01, DAMAGE_ENEMY_01 };

class AudioManager {
public:
  AudioManager();
  ~AudioManager();

  void playSfx(SFX sfx);
  void playMusic();

private:
  void initSFX();

  std::unordered_map<SFX, Mix_Chunk*> _sfxBank;
};
