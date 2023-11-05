#ifndef ENUMS
#define ENUMS

enum GameState { PLAY, EXIT };
enum InputState { RELEASED, PRESSED };
enum ControllerType { KEYBOARD, JOYSTICK };
enum GameObjectType { PLAYER, ENEMY, ITEM, WEAPON, PROJECTILE };
enum CharacterDirection { UP, DOWN, LEFT, RIGHT };
enum WeaponType { MELEE, RANGED };
enum TextureType { SPRITE, SPRITESHEET };
enum AnimationType { NONE, IDLE1, IDLE2, IDLE3, IDLE4, WALK1, WALK2, WALK3, WALK4, ATTACK1, ATTACK2, ATTACK3, ATTACK4 };

// clang-format off

// enum MouseButton { LEFT_MOUSE_BUTTON, RIGHT_MOUSE_BUTTON, MIDDLE_MOUSE_BUTTON, SCROLL_UP, SCROLL_DOWN };

enum JoystickType { PLAYSTATION, SWITCH, XBOX };
enum JoystickInput {
  // Face buttons
  B_UP, B_DOWN, B_LEFT, B_RIGHT,

  // Shoulder buttons
  L_TRIGGER, R_TRIGGER,
  L_BUMPER, R_BUMPER,

  // Analog sticks
  L_XL, L_XR, L_YU, L_YD, 
  R_XL, R_XR, R_YU, R_YD,
  L_3, R_3,  

  // D-pad buttons
  D_UP, D_DOWN, D_LEFT, D_RIGHT,

  // Menu buttons
  START, SELECT, TOUCHPAD
};
// clang-format on

#endif // ENUMS
