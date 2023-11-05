#include <AudioManager.h>

AudioManager::AudioManager() { initSFX(); }

AudioManager::~AudioManager() { Mix_CloseAudio(); }

void AudioManager::initSFX() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  _sfxBank = {
      {SFX::DAMAGE_PLAYER_01, Mix_LoadWAV("res/sfx/.WAV/damage_player_01.wav")},
      {SFX::DAMAGE_ENEMY_01, Mix_LoadWAV("res/sfx/.WAV/damage_enemy_01.wav")},
  };
}

void AudioManager::playSfx(SFX sfx) { Mix_PlayChannel(-1, _sfxBank[sfx], 0); }

void AudioManager::playMusic() {
  // Mix_Music* music = Mix_LoadMUS("res/sfx/.WAV/hit_01.wav");
  // Mix_PlayMusic(music, 0);
}
