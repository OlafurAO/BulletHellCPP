#include <headers/EventManager.h>

EventManager::EventManager() {
  // clang-format off
  _keyStates = {
    {SDLK_a, KeyState::RELEASED}, 
    {SDLK_d, KeyState::RELEASED}, 
    {SDLK_w, KeyState::RELEASED}, 
    {SDLK_s, KeyState::RELEASED},
    {SDLK_k, KeyState::RELEASED}
  };
  // clang-format on
}

EventManager::~EventManager() {}

void EventManager::pollEvents(GameState& gameState, Player*& player) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      gameState = GameState::EXIT;
      break;
    }

    SDL_Keycode keyCode;
    if (event.type == SDL_KEYDOWN) {
      keyCode = event.key.keysym.sym;
      processKeyEvent(keyCode, KeyState::PRESSED);
    } else if (event.type == SDL_KEYUP) {
      keyCode = event.key.keysym.sym;
      processKeyEvent(keyCode, KeyState::RELEASED);
    }
  }

  if (_keyStates[SDLK_k] == KeyState::PRESSED) {
    player->attack();
  }

  if (_keyStates[SDLK_a] == KeyState::PRESSED) {
    player->setMovementVectorX(-1);
  } else if (_keyStates[SDLK_d] == KeyState::PRESSED) {
    player->setMovementVectorX(1);
  } else {
    player->setMovementVectorX(0);
  }

  if (_keyStates[SDLK_w] == KeyState::PRESSED) {
    player->setMovementVectorY(-1);
  } else if (_keyStates[SDLK_s] == KeyState::PRESSED) {
    player->setMovementVectorY(1);
  } else {
    player->setMovementVectorY(0);
  }
}

void EventManager::processKeyEvent(SDL_Keycode keyCode, KeyState keyState) {
  try {
    if (_keyStates.find(keyCode) != _keyStates.end()) {
      _keyStates[keyCode] = keyState;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
