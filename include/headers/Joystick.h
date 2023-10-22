#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include <sdl2/SDL.h>

#include <Enums.h>
#include <Texture2D.h>

struct ButtonFrame {
  int spriteIndexPressed;
  int spriteIndexReleased;
};

class Joystick {
public:
  Joystick(int ID);
  ~Joystick();

  void cleanUp();
  void initButtonMap(const char* xboxTexKey, const char* psTexKey, const char* switchTexKey);

  void handleAxisInput(SDL_JoyAxisEvent jaxis);
  void handleButtonPressInput(SDL_JoyButtonEvent jbutton);
  void handleButtonReleaseInput(SDL_JoyButtonEvent jbutton);

  const char* getTextureKey();

  bool isAxisInputPressed(JoystickInput input);
  bool isButtonInputPressed(JoystickInput input);
  bool isJoystickActive();

private:
  void registerJoystickType();

  void registerJoystickEvent(JoystickInput input, InputState state);

  void mapNSJoystick();
  void mapPSJoystick();
  void mapXBJoystick();

  SDL_Joystick* _joystickController;

  const int _JOYSTICK_DEAD_ZONE = 8000;

  unsigned int _ID;
  const char* _textureKey;

  JoystickType _joystickType = JoystickType::XBOX;

  // clang-format off
  std::unordered_map<JoystickType, std::vector<const char*>> _joystickTypeMap = {
    // TODO: XBOX
    {JoystickType::PLAYSTATION, { "PS4", "PS5", "DualSense", "DualShock" }},
    {JoystickType::SWITCH, { "Switch", "Nintendo" }},
  };

  //std::unordered_map<JoyStickInput, ButtonFrame> _

  std::unordered_map<int, JoystickInput> _joystickButtonMap;

  std::unordered_map<JoystickInput, InputState> _joystickButtonStates = {
    // Face buttons
    {JoystickInput::B_UP,      InputState::RELEASED},
    {JoystickInput::B_DOWN,    InputState::RELEASED},
    {JoystickInput::B_LEFT,    InputState::RELEASED},
    {JoystickInput::B_RIGHT,   InputState::RELEASED},

    // Shoulder buttons
    {JoystickInput::L_BUMPER,  InputState::RELEASED},
    {JoystickInput::R_BUMPER,  InputState::RELEASED},

    // Analog buttons
    {JoystickInput::L_3,       InputState::RELEASED},
    {JoystickInput::R_3,       InputState::RELEASED},

    // D-pad buttons
    {JoystickInput::D_UP,      InputState::RELEASED},
    {JoystickInput::D_DOWN,    InputState::RELEASED},
    {JoystickInput::D_LEFT,    InputState::RELEASED},
    {JoystickInput::D_RIGHT,   InputState::RELEASED},

    // Menu buttons
    {JoystickInput::START,     InputState::RELEASED},
    {JoystickInput::SELECT,    InputState::RELEASED},
    {JoystickInput::TOUCHPAD,  InputState::RELEASED}
  };

  std::unordered_map<JoystickInput, InputState> _joystickAxisStates = {
    // Shoulder triggers
    {JoystickInput::L_TRIGGER, InputState::RELEASED},
    {JoystickInput::R_TRIGGER, InputState::RELEASED},

    // Analog sticks
    {JoystickInput::L_XL,       InputState::RELEASED},
    {JoystickInput::L_XR,       InputState::RELEASED},
    {JoystickInput::L_YU,       InputState::RELEASED},
    {JoystickInput::L_YD,       InputState::RELEASED},

    {JoystickInput::R_XL,       InputState::RELEASED},
    {JoystickInput::R_XR,       InputState::RELEASED},
    {JoystickInput::R_YU,       InputState::RELEASED},
    {JoystickInput::R_YD,       InputState::RELEASED},
  };
  // clang-format on

  bool _joystickAxesActive = false;
  bool _joystickButtonsActive = false;
};
