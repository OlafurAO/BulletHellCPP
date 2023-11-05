#pragma once

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include <sdl2/SDL.h>

#include <AudioManager.h>
#include <Character.h>
#include <Enemy.h>
#include <EntityManager.h>
#include <Enums.h>
#include <EventManager.h>
#include <GameObject.h>
#include <Item.h>
#include <Path.h>
#include <Player.h>
#include <Texture2D.h>
#include <WindowManager.h>

class Game {
public:
  Game();
  ~Game();

  void run();
  void init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags);

private:
  void gameLoop();

  double getDeltaTime(std::chrono::_V2::system_clock::time_point startTime, double& timer);

  WindowManager* _windowManager;
  ResourceManager* _resourceManager;
  AudioManager* _audioManager;
  EventManager* _eventManager;
  EntityManager* _entityManager;

  GameState _gameState;

  bool _debug = true;
};
