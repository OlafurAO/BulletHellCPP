#include <EventManager.h>

EventManager::EventManager(int screenWidth, int screenHeight) {
  _lastControllerTypeUsed = ControllerType::KEYBOARD;
  _joysticksDetected = SDL_NumJoysticks();
  _mousePosition = glm::vec2(screenWidth / 2, screenHeight / 2);
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
  bool foundKeyboardEvent = false;

  switch (event.type) {
  case SDL_KEYDOWN:
    registerKeyEvent(event.key.keysym.sym, InputState::PRESSED);
    foundKeyboardEvent = true;
    break;
  case SDL_KEYUP:
    registerKeyEvent(event.key.keysym.sym, InputState::RELEASED);
    foundKeyboardEvent = true;
    break;
  case SDL_MOUSEMOTION:
    registerMouseMotionEvent(event.motion.x, event.motion.y);
    foundKeyboardEvent = true;
    break;
  case SDL_MOUSEBUTTONDOWN:
    registerMouseButtonEvent(event.button.button, InputState::PRESSED);
    foundKeyboardEvent = true;
    break;
  case SDL_MOUSEBUTTONUP:
    registerMouseButtonEvent(event.button.button, InputState::RELEASED);
    foundKeyboardEvent = true;
    break;
  default:
    break;
  }

  if (foundKeyboardEvent) {
    _lastControllerTypeUsed = ControllerType::KEYBOARD;
  }
}

void EventManager::pollJoystickEvents(SDL_Event event) {
  if (event.type == SDL_JOYAXISMOTION) {
    _joysticks[event.jaxis.which]->handleAxisInput(event.jaxis);

    if (_joysticks[event.jaxis.which]->isJoystickActive()) {
      _lastControllerTypeUsed = ControllerType::JOYSTICK;
    }
  }

  bool isJoystickActive = false;
  if (event.type == SDL_JOYBUTTONDOWN) {
    _joysticks[event.jbutton.which]->handleButtonPressInput(event.jbutton);
    isJoystickActive = _joysticks[event.jbutton.which]->isJoystickActive();
  } else if (event.type == SDL_JOYBUTTONUP) {
    _joysticks[event.jbutton.which]->handleButtonReleaseInput(event.jbutton);
    isJoystickActive = _joysticks[event.jbutton.which]->isJoystickActive();
  }

  if (isJoystickActive) {
    _lastControllerTypeUsed = ControllerType::JOYSTICK;
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

  player->updateCrosshair(_mousePosition.x, _mousePosition.y);
  if (_mouseButtonStates[SDL_BUTTON_LEFT] == InputState::PRESSED) {
    player->attack();
  } /*else if (_mouseButtonStates[SDL_BUTTON_RIGHT] == InputState::PRESSED) {
  }
  if (_mouseButtonStates[SDL_BUTTON_LEFT] == InputState::PRESSED) {
  }*/
}

void EventManager::processJoystickEvents(Player* player) {
  if (_joysticks[0]->isButtonInputPressed(JoystickInput::B_LEFT)) {
    player->attack();
  }

  glm::vec2 crossHairVelocity = glm::vec2(0);

  // calculate angle??
  if (_joysticks[0]->isAxisInputPressed(JoystickInput::R_XL)) {
    crossHairVelocity -= glm::vec2(1.f, 0);
  } else if (_joysticks[0]->isAxisInputPressed(JoystickInput::R_XR)) {
    crossHairVelocity += glm::vec2(1.f, 0);
  }

  if (_joysticks[0]->isAxisInputPressed(JoystickInput::R_YU)) {
    crossHairVelocity -= glm::vec2(0, 1.f);
  } else if (_joysticks[0]->isAxisInputPressed(JoystickInput::R_YD)) {
    crossHairVelocity += glm::vec2(0, 1.f);
  }

  player->updateJoystickCrosshair(crossHairVelocity);

  // TODO: check all connected joysticks
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

void EventManager::registerMouseButtonEvent(Uint8 buttonCode, InputState buttonState) {
  if (_mouseButtonStates.find(buttonCode) != _mouseButtonStates.end()) {
    _mouseButtonStates[buttonCode] = buttonState;
  }
}

void EventManager::registerMouseMotionEvent(int x, int y) { _mousePosition = glm::vec2(x, y); }

std::vector<Joystick*> EventManager::getJoysticks() { return _joysticks; }

int EventManager::getJoystickCount() { return _joysticksDetected; }
