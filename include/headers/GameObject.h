#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sdl2/SDL.h>

#include <Animator.h>
#include <Enums.h>
#include <Hitbox.h>
#include <Texture2D.h>

class GameObject {
public:
  GameObject(GameObjectType objectType);
  GameObject(GameObjectType objectType, float scale);
  GameObject(GameObjectType objectType, float scale, float speed);
  ~GameObject();

  virtual void update(double deltaTime);

  virtual void initAnimator();

  virtual void setMovementVectorX(int direction);
  virtual void setMovementVectorY(int direction);
  virtual void registerTexture(const char* texKey, Texture2D& tex, SDL_Renderer* renderer, unsigned int referenceFrameIndex);
  virtual void registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop);
  virtual void playAnimation(AnimationType type);
  virtual void setPosition(glm::vec3 newPos);
  virtual void setZRotation(double angle);

  virtual Hitbox* getHitbox();
  virtual SDL_FRect getHitboxBounds();
  virtual glm::vec2 getHitboxCenterPoint();

  virtual SDL_Color getColor();

  virtual SDL_FRect getPositionRect();
  virtual glm::vec3 getPositionVec();

  virtual int getDirection();
  virtual double getZRotation();

  virtual const char* getTextureKey();
  virtual unsigned int getSpriteIndex();

  GameObjectType getObjectType();

protected:
  void setCanMove(bool canMove);

  Animator* _animator;
  Hitbox* _hitbox;

  SDL_Color _color = g_DEFAULT_COLOR;

  glm::vec3 _position;
  glm::vec3 _movementVector;
  glm::vec3 _prevMovementVector;
  glm::vec3 _scale;

  int _direction = 1;

  double _zRotation = 0.f;

  bool _canMove;

private:
  void init(GameObjectType objectType);
  void initScale(float scale);
  void initSpeed(float speed);
  void initHitbox(SDL_Renderer* renderer, Texture2D& tex, unsigned int referenceFrameIndex);

  void updateHitboxPos(glm::vec3 newPos);

  void updateMovement(double deltaTime);
  void updatePrevMovementVector();

  GameObjectType _objectType;

  const char* _textureKey;
  std::pair<int, int> _texFrameSize;

  float _speed = 1.f;
};
