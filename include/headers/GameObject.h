#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sdl2/SDL.h>

#include <Animator.h>
#include <Enums.h>

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
  virtual void registerTextureKey(const char* texKey);
  virtual void registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop);
  virtual void playAnimation(AnimationType type);

  virtual SDL_Rect getPositionRect();
  virtual glm::vec3 getPositionVec();

  virtual int getDirection();

  virtual const char* getTextureKey();
  virtual unsigned int getSpriteIndex();

  virtual int getHealth();

  GameObjectType getObjectType();

protected:
  void setCanMove(bool canMove);

  Animator* _animator;

  glm::vec3 _position;
  glm::vec3 _movementVector;
  glm::vec3 _prevMovementVector;
  glm::vec3 _scale;

  int _direction = 1;

  bool _canMove;

private:
  void init(GameObjectType objectType);
  void initScale(float scale);
  void initSpeed(float speed);

  void updateMovement(double deltaTime);
  void updatePrevMovementVector();
  void updateRotationOnMoveX(int direction);

  const char* _textureKey;

  GameObjectType _objectType;

  float _speed = 1.f;
  int _health = 10;
  int _damage = 1;
};
