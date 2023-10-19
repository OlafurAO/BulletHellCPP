#ifndef ENUMS
#define ENUMS

enum GameState { PLAY, EXIT };
enum KeyState { RELEASED, PRESSED };
enum GameObjectType { PLAYER, ENEMY };
enum CharacterDirection { UP, DOWN, LEFT, RIGHT };
enum WeaponType { MELEE, RANGED };
enum TextureType { SPRITE, SPRITESHEET };
enum AnimationType { NONE, IDLE1, IDLE2, IDLE3, IDLE4, WALK1, WALK2, WALK3, WALK4, ATTACK1, ATTACK2, ATTACK3, ATTACK4 };

#endif // ENUMS
