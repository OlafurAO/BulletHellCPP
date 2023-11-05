#include <Game.h>

Game::Game() {
  _eventManager = nullptr;
  _windowManager = nullptr;
}

Game::~Game() {
  _windowManager->cleanUp();
  delete _eventManager;
  delete _entityManager;
  delete _windowManager;
  delete _audioManager;
  delete _resourceManager;
  SDL_Quit();
}

void Game::init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags) {
  _resourceManager = new ResourceManager();

  _windowManager = new WindowManager(_resourceManager);
  _windowManager->init(title, wPosX, wPosY, windowW, windowH, flags);

  _resourceManager->setRenderer(_windowManager->getRenderer());

  _entityManager = new EntityManager(_resourceManager, _audioManager);
  _audioManager = new AudioManager();
}

void Game::run() { gameLoop(); }

void Game::gameLoop() {
  std::pair<int, int> windowSize = _windowManager->getScreenSize();
  _eventManager = new EventManager(windowSize.first, windowSize.second);

  _entityManager->initEntities();

  if (_eventManager->getJoystickCount() > 0) {
    const char* xboxTexKey = "gamepad_xbox";
    const char* psTexKey = "gamepad_playstation";
    const char* nsTexKey = "gamepad_switch";

    _resourceManager->loadTexture(Path("xbox_gamepad.png", ResType::SPRITE_UI), xboxTexKey, TextureType::SPRITESHEET, 12, 12);
    _resourceManager->loadTexture(Path("switch_gamepad.png", ResType::SPRITE_UI), nsTexKey, TextureType::SPRITESHEET, 12, 12);
    _resourceManager->loadTexture(Path("ps_gamepad.png", ResType::SPRITE_UI), psTexKey, TextureType::SPRITESHEET, 12, 12);

    _eventManager->initJoysticks(xboxTexKey, psTexKey, nsTexKey);
  }

  _gameState = GameState::PLAY;
  std::chrono::_V2::system_clock::time_point startTime = std::chrono::high_resolution_clock::now();
  double timer = 0.0;

  while (_gameState != GameState::EXIT) {
    double deltaTime = getDeltaTime(startTime, timer);
    _eventManager->pollEvents(_gameState, _entityManager->getPlayer());
    _windowManager->renderScreen();

    _windowManager->renderGameObjects(_entityManager->getAllGameObjects());
    _entityManager->updateEntities(deltaTime);

    if (_debug) {
      _windowManager->renderDebugProps(_eventManager->getJoysticks());
    }

    _windowManager->presentScreen();

    // Sleep to control frame rate (optional, adjust as needed)
    // std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}

double Game::getDeltaTime(std::chrono::_V2::system_clock::time_point startTime, double& timer) {
  auto currentTime = std::chrono::high_resolution_clock::now();
  double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

  double deltaTime = elapsedTime - timer;
  timer = elapsedTime;

  return deltaTime;
}
