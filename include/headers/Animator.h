#pragma once

#include <Enums.h>
#include <unordered_map>
#include <vector>

#include <Globals.h>

struct Animation {
  int* spriteIndices;
  unsigned int frameCount;
  bool loopAnimation;
};

class Animator {
public:
  Animator();
  ~Animator();

  void update(double deltaTime);

  void playAnimation(AnimationType type);
  void registerAnimation(AnimationType type, int* spriteIndices, unsigned int frameCount, bool loop);

  AnimationType getCurrentAnimation();
  AnimationType getPrevAnimation();
  unsigned int getCurrentSpriteIndex();

  bool isPlayingAnimation();

private:
  void nextFrame();

  Animation initAnimation(int* spriteIndices, unsigned int frameCount, bool loop);

  std::unordered_map<AnimationType, Animation> _animations;

  double _animationTimer;

  AnimationType _currentAnimation;
  AnimationType _prevAnimation;
  unsigned int _currentSpriteIndex;
  unsigned int _maxIndex;
};
