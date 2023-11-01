#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <sdl2/SDL.h>

#include <Enums.h>
#include <Joystick.h>
#include <Player.h>

class EventManager {
public:
  EventManager(int screenWidth, int screenHeight);
  ~EventManager();

  void initJoysticks(const char* xboxTexKey, const char* psTexKey, const char* switchTexKey);

  void pollEvents(GameState& gameState, Player*& player);

  std::vector<Joystick*> getJoysticks();

  int getJoystickCount();

private:
  void pollKeyboardEvents(SDL_Event event);
  void pollJoystickEvents(SDL_Event event);

  void processKeyboardEvents(Player* player);
  void processJoystickEvents(Player* player);

  void registerKeyEvent(SDL_Keycode keyCode, InputState keyState);
  void registerMouseButtonEvent(Uint8 buttonCode, InputState buttonState);
  void registerMouseMotionEvent(int x, int y);

  const int _MAX_CONTROLLER_COUNT = 4;

  ControllerType _lastControllerTypeUsed;

  std::vector<Joystick*> _joysticks;

  int _joysticksDetected = 0;

  // clang-format off
  std::unordered_map<SDL_Keycode, InputState> _keyStates = {
    {SDLK_a, InputState::RELEASED},
    {SDLK_d, InputState::RELEASED},
    {SDLK_w, InputState::RELEASED},
    {SDLK_s, InputState::RELEASED},
    {SDLK_k, InputState::RELEASED}
  };

  std::unordered_map<Uint8, InputState> _mouseButtonStates = {
    {SDL_BUTTON_LEFT,   InputState::RELEASED},
    {SDL_BUTTON_RIGHT,  InputState::RELEASED},
    {SDL_BUTTON_MIDDLE, InputState::RELEASED},
    
    // TODO: handle scroll
    //{SCROLL_UP,           InputState::RELEASED},
    //{SCROLL_DOWN,         InputState::RELEASED},
  };



  glm::vec2 _mousePosition;
  // clang-format on
};
