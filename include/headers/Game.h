#pragma once
#pragma once
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include <sdl2/SDL.h>

#include <Enemy.h>
#include <Enums.h>
#include <EventManager.h>
#include <GameObject.h>
#include <Player.h>
#include <WindowManager.h>

class Game {
public:
  Game();
  ~Game();

  void run();
  void init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags);

private:
  void gameLoop();
  void updateGameObjects(double deltaTime);

  double getDeltaTime(std::chrono::_V2::system_clock::time_point startTime, double& timer);

  WindowManager* _windowManager;
  EventManager* _eventManager;
  Player* _player;

  std::vector<GameObject*> _gameObjects;

  GameState _gameState;
};
