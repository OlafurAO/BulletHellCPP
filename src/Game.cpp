#include <Game.h>

Game::Game() {
  _eventManager = nullptr;
  _windowManager = nullptr;
  _player = nullptr;
}

Game::~Game() {
  _gameObjects.clear();
  _windowManager->cleanUp();

  delete _player;
  delete _eventManager;
  delete _windowManager;
  SDL_Quit();
}

void Game::init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags) {
  _windowManager = new WindowManager();
  _windowManager->init(title, wPosX, wPosY, windowW, windowH, flags);
}

void Game::run() { gameLoop(); }

void Game::gameLoop() {
  // TODO: set key inputs, set callbacks
  _eventManager = new EventManager();

  //////////////////////////////////////////////////////////////
  _player = new Player(GameObjectType::PLAYER, 1.f, 0.25f);

  const char* textureKey = "player";
  _windowManager->initTexture("res/sprites/characters/player.png", textureKey, TextureType::SPRITESHEET, 10, 6);
  _player->registerTextureKey(textureKey);

  _player->initAnimator();
  _player->registerAnimation(AnimationType::IDLE1, new int[6]{0, 1, 2, 3, 4, 5}, 6, true);
  _player->registerAnimation(AnimationType::IDLE2, new int[6]{6, 7, 8, 9, 10, 11}, 6, true);
  _player->registerAnimation(AnimationType::IDLE3, new int[6]{12, 13, 14, 15, 16, 17}, 6, true);

  _player->registerAnimation(AnimationType::WALK1, new int[6]{18, 19, 20, 21, 22, 23}, 6, true);
  _player->registerAnimation(AnimationType::WALK2, new int[6]{24, 25, 26, 27, 28, 29}, 6, true);
  _player->registerAnimation(AnimationType::WALK3, new int[6]{30, 31, 32, 33, 34, 35}, 6, true);

  _player->registerAnimation(AnimationType::ATTACK1, new int[3]{36, 37, 38}, 3, false);
  _player->registerAnimation(AnimationType::ATTACK2, new int[3]{42, 43, 44}, 3, false);
  _player->registerAnimation(AnimationType::ATTACK3, new int[3]{48, 49, 50}, 3, false);

  _player->playAnimation(AnimationType::IDLE1);

  Enemy* enemy = new Enemy(GameObjectType::ENEMY, 4000.f, 2500.f, 0.75f, 0.1f);

  const char* textureKey2 = "slime";
  _windowManager->initTexture("res/sprites/characters/slime.png", textureKey2, TextureType::SPRITESHEET, 5, 7);
  enemy->registerTextureKey(textureKey2);

  enemy->initAnimator();
  enemy->registerAnimation(AnimationType::IDLE1, new int[4]{0, 1, 2, 3}, 4, true);
  enemy->playAnimation(AnimationType::IDLE1);

  _gameObjects.push_back(_player);
  _gameObjects.push_back(enemy);
  /////////////////////////////////////////////////////////

  _gameState = GameState::PLAY;
  std::chrono::_V2::system_clock::time_point startTime = std::chrono::high_resolution_clock::now();
  double timer = 0.0;

  while (_gameState != GameState::EXIT) {
    _eventManager->pollEvents(_gameState, _player);
    _windowManager->renderScreen(_gameObjects);

    double deltaTime = getDeltaTime(startTime, timer);
    updateGameObjects(deltaTime);

    // Sleep to control frame rate (optional, adjust as needed)
    // std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}

void Game::updateGameObjects(double deltaTime) {
  for (const auto& gameObj : _gameObjects) {
    if (gameObj->getObjectType() == GameObjectType::ENEMY) {
      Enemy* enemy = dynamic_cast<Enemy*>(gameObj);
      if (enemy != nullptr) {
        enemy->update(_player, deltaTime);
      }
    } else if (gameObj->getObjectType() == GameObjectType::PLAYER) {
      Player* player = dynamic_cast<Player*>(gameObj);
      if (player != nullptr) {
        player->update();
      }
    }

    Character* character = dynamic_cast<Character*>(gameObj);
    if (character != nullptr) {
      character->update();
    }

    gameObj->update(deltaTime);
  }
}

double Game::getDeltaTime(std::chrono::_V2::system_clock::time_point startTime, double& timer) {
  auto currentTime = std::chrono::high_resolution_clock::now();
  double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

  double deltaTime = elapsedTime - timer;
  timer = elapsedTime;

  return deltaTime;
}
