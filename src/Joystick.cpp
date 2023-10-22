#include <Joystick.h>

Joystick::Joystick(int ID) : _ID(ID) {
  SDL_JoystickOpen(ID);
  registerJoystickType();
}

Joystick::~Joystick() {}

void Joystick::cleanUp() { SDL_JoystickClose(_joystickController); }

void Joystick::initButtonMap(const char* xboxTexKey, const char* psTexKey, const char* switchTexKey) {
  if (_joystickType == JoystickType::SWITCH) {
    mapNSJoystick();
    _textureKey = switchTexKey;
  } else if (_joystickType == JoystickType::PLAYSTATION) {
    mapPSJoystick();
    _textureKey = psTexKey;
  } else {
    mapNSJoystick();
    _textureKey = xboxTexKey;
  }
}

void Joystick::handleAxisInput(SDL_JoyAxisEvent jaxis) {
  // Are the analog sticks not being moved enough to bother checking?
  if (jaxis.value >= -_JOYSTICK_DEAD_ZONE && jaxis.value <= _JOYSTICK_DEAD_ZONE) {
    _joystickAxesActive = false;
  } else {
    _joystickAxesActive = true;
  }

  // L-Analog stick: X-axis
  if (jaxis.axis == 0) {
    if (jaxis.value < -_JOYSTICK_DEAD_ZONE) {
      registerJoystickEvent(JoystickInput::L_XL, InputState::PRESSED);
      registerJoystickEvent(JoystickInput::L_XR, InputState::RELEASED);
    } else if (jaxis.value > _JOYSTICK_DEAD_ZONE) {
      registerJoystickEvent(JoystickInput::L_XR, InputState::PRESSED);
      registerJoystickEvent(JoystickInput::L_XL, InputState::RELEASED);
    } else {
      registerJoystickEvent(JoystickInput::L_XL, InputState::RELEASED);
      registerJoystickEvent(JoystickInput::L_XR, InputState::RELEASED);
    }
  }
  // L-Analog stick: Y-axis
  if (jaxis.axis == 1) {
    if (jaxis.value < -_JOYSTICK_DEAD_ZONE) {
      registerJoystickEvent(JoystickInput::L_YU, InputState::PRESSED);
      registerJoystickEvent(JoystickInput::L_YD, InputState::RELEASED);
    } else if (jaxis.value > _JOYSTICK_DEAD_ZONE) {
      registerJoystickEvent(JoystickInput::L_YD, InputState::PRESSED);
      registerJoystickEvent(JoystickInput::L_YU, InputState::RELEASED);
    } else {
      registerJoystickEvent(JoystickInput::L_YU, InputState::RELEASED);
      registerJoystickEvent(JoystickInput::L_YD, InputState::RELEASED);
    }
  }

  // R-Analog stick: X-axis
  if (jaxis.axis == 2) {
    if (jaxis.value < -_JOYSTICK_DEAD_ZONE) {
      std::cout << "R-xDir LEFT" << std::endl;
    } else if (jaxis.value > _JOYSTICK_DEAD_ZONE) {
      std::cout << "R-xDir RIGHT" << std::endl;
    }
  }

  // R-Analog stick: Y-axis
  if (jaxis.axis == 3) {
    if (jaxis.value < -_JOYSTICK_DEAD_ZONE) {
      std::cout << "R-yDir UP" << std::endl;
    } else if (jaxis.value > _JOYSTICK_DEAD_ZONE) {
      std::cout << "R-yDir DOWN" << std::endl;
    }
  }

  // Left Trigger
  if (jaxis.axis == 4) {
    if (jaxis.value > _JOYSTICK_DEAD_ZONE / 2) {
      std::cout << "L-Trigger" << std::endl;
    }
  }

  // Right Trigger
  if (jaxis.axis == 5) {
    if (jaxis.value > _JOYSTICK_DEAD_ZONE / 2) {
      std::cout << "R-Trigger" << std::endl;
    }
  }
}

void Joystick::handleButtonPressInput(SDL_JoyButtonEvent jbutton) {
  int buttonIndex = static_cast<int>(jbutton.button);
  JoystickInput input = _joystickButtonMap[buttonIndex];
  _joystickButtonStates[input] = InputState::PRESSED;

  std::cout << buttonIndex << std::endl;
  _joystickButtonsActive = true;
}

void Joystick::handleButtonReleaseInput(SDL_JoyButtonEvent jbutton) {
  int buttonIndex = static_cast<int>(jbutton.button);
  JoystickInput input = _joystickButtonMap[buttonIndex];
  _joystickButtonStates[input] = InputState::RELEASED;

  _joystickButtonsActive = false;
}

const char* Joystick::getTextureKey() { return _textureKey; }

bool Joystick::isAxisInputPressed(JoystickInput input) { return _joystickAxisStates[input] == InputState::PRESSED; }

bool Joystick::isButtonInputPressed(JoystickInput input) { return _joystickButtonStates[input] == InputState::PRESSED; }

bool Joystick::isJoystickActive() { return _joystickAxesActive || _joystickButtonsActive; }

void Joystick::registerJoystickType() {
  const char* name = SDL_JoystickNameForIndex(_ID);

  for (const auto& type : _joystickTypeMap) {
    for (const char* typeStr : type.second) {
      if (SDL_strstr(name, typeStr)) {
        _joystickType = type.first;
        return;
      }
    }
  }
}

void Joystick::registerJoystickEvent(JoystickInput input, InputState state) {
  if (_joystickAxisStates.find(input) != _joystickAxisStates.end()) {
    _joystickAxisStates[input] = state;
  } else if (_joystickButtonStates.find(input) != _joystickButtonStates.end()) {
    _joystickButtonStates[input] = state;
  }
}

void Joystick::mapNSJoystick() {
  _joystickButtonMap = {
      // Face buttons
      {2, JoystickInput::B_UP},
      {1, JoystickInput::B_DOWN},
      {3, JoystickInput::B_LEFT},
      {0, JoystickInput::B_RIGHT},

      // Shoulder buttons
      {9, JoystickInput::L_BUMPER},
      {10, JoystickInput::R_BUMPER},

      // Analog buttons
      {7, JoystickInput::L_3},
      {8, JoystickInput::R_3},

      // D-pad buttons
      {11, JoystickInput::D_UP},
      {12, JoystickInput::D_DOWN},
      {13, JoystickInput::D_LEFT},
      {14, JoystickInput::D_RIGHT},

      // Menu buttons
      {6, JoystickInput::START},
      {4, JoystickInput::SELECT},
  };
}

void Joystick::mapPSJoystick() {
  _joystickButtonMap = {
      // Face buttons
      {3, JoystickInput::B_UP},
      {0, JoystickInput::B_DOWN},
      {2, JoystickInput::B_LEFT},
      {1, JoystickInput::B_RIGHT},

      // Shoulder buttons
      {9, JoystickInput::L_BUMPER},
      {10, JoystickInput::R_BUMPER},

      // Analog buttons
      {7, JoystickInput::L_3},
      {8, JoystickInput::R_3},

      // D-pad buttons
      {11, JoystickInput::D_UP},
      {12, JoystickInput::D_DOWN},
      {13, JoystickInput::D_LEFT},
      {14, JoystickInput::D_RIGHT},

      // Menu buttons
      {6, JoystickInput::START},
      {4, JoystickInput::SELECT},
      {15, JoystickInput::TOUCHPAD},
  };
}

void Joystick::mapXBJoystick() {}
