#pragma once
#include <iostream>
#include <unordered_map>

#include <sdl2/SDL.h>

#include <Enums.h>
#include <Player.h>

class EventManager {
public:
  EventManager();
  ~EventManager();

  void pollEvents(GameState& gameState, Player*& player);

private:
  void processKeyEvent(SDL_Keycode keyCode, KeyState keyState);

  std::unordered_map<SDL_Keycode, KeyState> _keyStates;
};
