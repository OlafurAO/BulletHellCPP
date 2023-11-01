#include <Game.h>

Game::Game() {
  _eventManager = nullptr;
  _windowManager = nullptr;
  _player = nullptr;
}

Game::~Game() {
  _characters.clear();
  _items.clear();

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
  std::pair<int, int> windowSize = _windowManager->getScreenSize();
  _eventManager = new EventManager(windowSize.first, windowSize.second);

  //////////////////////////////////////////////////////////////
  _player = new Player(GameObjectType::PLAYER, 1.f, 0.2f);

  const char* textureKey = "player";
  Texture2D& playerTex = _windowManager->initTexture("res/sprites/characters/player.png", textureKey, TextureType::SPRITESHEET, 10, 6);
  _player->registerTexture(textureKey, playerTex, _windowManager->getRenderer(), 0);

  _player->initAnimator();
  _player->registerAnimation(AnimationType::IDLE1, new int[6]{6, 7, 8, 9, 10, 11}, 6, true);
  _player->registerAnimation(AnimationType::WALK1, new int[6]{24, 25, 26, 27, 28, 29}, 6, true);
  _player->registerAnimation(AnimationType::ATTACK1, new int[3]{42, 43, 44}, 3, false);

  _player->playAnimation(AnimationType::IDLE1);

  Enemy* enemy = new Enemy(GameObjectType::ENEMY, 4000.f, 2500.f, 0.75f, 0.1f);

  const char* textureKey2 = "slime";
  Texture2D& slimeTex = _windowManager->initTexture("res/sprites/characters/slime.png", textureKey2, TextureType::SPRITESHEET, 5, 7);
  enemy->registerTexture(textureKey2, slimeTex, _windowManager->getRenderer(), 2);

  enemy->initAnimator();
  enemy->registerAnimation(AnimationType::IDLE1, new int[4]{0, 1, 2, 3}, 4, true);
  enemy->playAnimation(AnimationType::IDLE1);

  _characters.push_back(_player);
  _characters.push_back(enemy);

  if (_eventManager->getJoystickCount() > 0) {
    const char* xboxTexKey = "gamepad_xbox";
    const char* psTexKey = "gamepad_playstation";
    const char* nsTexKey = "gamepad_switch";

    _windowManager->initTexture("res/sprites/gamepads/xbox_gamepad.png", xboxTexKey, TextureType::SPRITESHEET, 12, 12);
    _windowManager->initTexture("res/sprites/gamepads/switch_gamepad.png", nsTexKey, TextureType::SPRITESHEET, 12, 12);
    _windowManager->initTexture("res/sprites/gamepads/ps_gamepad.png", psTexKey, TextureType::SPRITESHEET, 12, 12);

    _eventManager->initJoysticks(xboxTexKey, psTexKey, nsTexKey);
  }

  const char* gunsTexKey = "weapons_guns";
  Texture2D& gunTex = _windowManager->initTexture("res/sprites/weapons/revolver.png", gunsTexKey, TextureType::SPRITESHEET, 1, 1);

  Weapon* revolver = new Weapon(GameObjectType::WEAPON, 0.25f);
  revolver->registerTexture(gunsTexKey, gunTex, _windowManager->getRenderer(), 0);
  _player->equipWeapon(revolver);
  /////////////////////////////////////////////////////////

  _gameState = GameState::PLAY;
  std::chrono::_V2::system_clock::time_point startTime = std::chrono::high_resolution_clock::now();
  double timer = 0.0;

  while (_gameState != GameState::EXIT) {
    double deltaTime = getDeltaTime(startTime, timer);

    _eventManager->pollEvents(_gameState, _player);
    _windowManager->renderScreen();

    _windowManager->renderGameObjects(_characters, _items);

    updateGameObjects(deltaTime);

    if (_debug) {
      _windowManager->renderDebugProps(_eventManager->getJoysticks());
    }

    _windowManager->presentScreen();

    // Sleep to control frame rate (optional, adjust as needed)
    // std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}

void Game::updateGameObjects(double deltaTime) {
  for (const auto& character : _characters) {
    if (character->getObjectType() == GameObjectType::ENEMY) {
      Enemy* enemy = dynamic_cast<Enemy*>(character);
      if (enemy != nullptr) {
        enemy->update(_player, deltaTime);
      }
    } else if (character->getObjectType() == GameObjectType::PLAYER) {
      Player* player = dynamic_cast<Player*>(character);
      if (player != nullptr) {
        player->update();
      }
    }

    character->update(deltaTime);

    GameObject* obj = dynamic_cast<GameObject*>(character);
    if (obj != nullptr) {
      obj->update(deltaTime);
    }
  }
}

double Game::getDeltaTime(std::chrono::_V2::system_clock::time_point startTime, double& timer) {
  auto currentTime = std::chrono::high_resolution_clock::now();
  double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

  double deltaTime = elapsedTime - timer;
  timer = elapsedTime;

  return deltaTime;
}
