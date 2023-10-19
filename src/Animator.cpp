#include <Animator.h>

Animator::Animator() {
  _currentAnimation = AnimationType::NONE;
  _currentSpriteIndex = 0;
  _animationTimer = 0.0;
}

Animator::~Animator() { _animations.clear(); }

#include <iostream>

void Animator::update(double deltaTime) {
  _animationTimer += deltaTime;
  if (_animationTimer >= g_animationTickRate) {
    nextFrame();
  }
}

void Animator::playAnimation(AnimationType type) {
  if (_currentAnimation != type && _animations.count(type) > 0) {
    _prevAnimation = _currentAnimation;
    _currentAnimation = type;
    _currentSpriteIndex = _animations[type].spriteIndices[0];
  }
}

void Animator::registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop) {
  _animations[type] = initAnimation(spriteIndices, frameCount, loop);
}

void Animator::nextFrame() {
  Animation currentAnim = _animations[_currentAnimation];
  int* spriteIndices = currentAnim.spriteIndices;
  int animSize = currentAnim.frameCount;
  int lastFrameIndex = spriteIndices[animSize - 1];

  _animationTimer = 0.0;
  if (_currentSpriteIndex > lastFrameIndex - 1) {
    if (currentAnim.loopAnimation) {
      _currentSpriteIndex = spriteIndices[0];
    } else {
      _currentAnimation = AnimationType::NONE;
    }
  } else {
    _currentSpriteIndex++;
  }
}

Animation Animator::initAnimation(int* spriteIndices, unsigned int frameCount, bool loop) {
  Animation animation;
  animation.spriteIndices = spriteIndices;
  animation.frameCount = frameCount;
  animation.loopAnimation = loop;

  return animation;
}

AnimationType Animator::getCurrentAnimation() { return _currentAnimation; }

AnimationType Animator::getPrevAnimation() { return _prevAnimation; }

unsigned int Animator::getCurrentSpriteIndex() { return _currentSpriteIndex; }

bool Animator::isPlayingAnimation() { return _currentAnimation != AnimationType::NONE; }
