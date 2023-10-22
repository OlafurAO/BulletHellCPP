#include <EventManager.h>

EventManager::EventManager() {
  _lastControllerTypeUsed = ControllerType::KEYBOARD;
  _joysticksDetected = SDL_NumJoysticks();
}

EventManager::~EventManager() {
  for (int i = 0; i < _joysticks.size(); i++) {
    _joysticks[i]->cleanUp();
  }
  _joysticks.clear();
}

void EventManager::initJoysticks(const char* xboxTexKey, const char* psTexKey, const char* switchTexKey) {
  if (_joysticksDetected > 0) {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    int maxCount = _joysticksDetected <= _MAX_CONTROLLER_COUNT ? _joysticksDetected : _MAX_CONTROLLER_COUNT;
    for (int i = 0; i < maxCount; i++) {
      _joysticks.push_back(new Joystick(i));
      _joysticks[i]->initButtonMap(xboxTexKey, psTexKey, switchTexKey);
    }
  }
}

void EventManager::pollEvents(GameState& gameState, Player*& player) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      gameState = GameState::EXIT;
      break;
    }

    pollKeyboardEvents(event);
    pollJoystickEvents(event);
  }

  if (_lastControllerTypeUsed == ControllerType::KEYBOARD) {
    processKeyboardEvents(player);
  } else {
    processJoystickEvents(player);
  }
}

void EventManager::pollKeyboardEvents(SDL_Event event) {
  SDL_Keycode keyCode;
  if (event.type == SDL_KEYDOWN) {
    registerKeyEvent(event.key.keysym.sym, InputState::PRESSED);

    // TODO: FIX
    _lastControllerTypeUsed = ControllerType::KEYBOARD;
  } else if (event.type == SDL_KEYUP) {
    registerKeyEvent(event.key.keysym.sym, InputState::RELEASED);

    // TODO: FIX
    _lastControllerTypeUsed = ControllerType::KEYBOARD;
  }
}

void EventManager::pollJoystickEvents(SDL_Event event) {
  if (event.type == SDL_JOYAXISMOTION) {
    _joysticks[event.jaxis.which]->handleAxisInput(event.jaxis);

    // TODO: FIX
    if (_joysticks[event.jaxis.which]->isJoystickActive()) {
      _lastControllerTypeUsed = ControllerType::JOYSTICK;
    }
  }

  if (event.type == SDL_JOYBUTTONDOWN) {
    _joysticks[event.jbutton.which]->handleButtonPressInput(event.jbutton);

    // TODO: FIX
    if (_joysticks[event.jbutton.which]->isJoystickActive()) {
      _lastControllerTypeUsed = ControllerType::JOYSTICK;
    }
  } else if (event.type == SDL_JOYBUTTONUP) {
    _joysticks[event.jbutton.which]->handleButtonReleaseInput(event.jbutton);
  }
}

void EventManager::processKeyboardEvents(Player* player) {
  if (_keyStates[SDLK_k] == InputState::PRESSED) {
    player->attack();
  }

  if (_keyStates[SDLK_a] == InputState::PRESSED) {
    player->setMovementVectorX(-1);
  } else if (_keyStates[SDLK_d] == InputState::PRESSED) {
    player->setMovementVectorX(1);
  } else {
    player->setMovementVectorX(0);
  }

  if (_keyStates[SDLK_w] == InputState::PRESSED) {
    player->setMovementVectorY(-1);
  } else if (_keyStates[SDLK_s] == InputState::PRESSED) {
    player->setMovementVectorY(1);
  } else {
    player->setMovementVectorY(0);
  }
}

void EventManager::processJoystickEvents(Player* player) {
  if (_joysticks[0]->isButtonInputPressed(JoystickInput::B_LEFT)) {
    player->attack();
  }

  // TODO: check all joysticks
  if (_joysticks[0]->isAxisInputPressed(JoystickInput::L_XL)) {
    player->setMovementVectorX(-1);
  } else if (_joysticks[0]->isAxisInputPressed(JoystickInput::L_XR)) {
    player->setMovementVectorX(1);
  } else {
    player->setMovementVectorX(0);
  }

  if (_joysticks[0]->isAxisInputPressed(JoystickInput::L_YU)) {
    player->setMovementVectorY(-1);
  } else if (_joysticks[0]->isAxisInputPressed(JoystickInput::L_YD)) {
    player->setMovementVectorY(1);
  } else {
    player->setMovementVectorY(0);
  }
}

void EventManager::registerKeyEvent(SDL_Keycode keyCode, InputState keyState) {
  if (_keyStates.find(keyCode) != _keyStates.end()) {
    _keyStates[keyCode] = keyState;
  }
}

std::vector<Joystick*> EventManager::getJoysticks() { return _joysticks; }

int EventManager::getJoystickCount() { return _joysticksDetected; }
