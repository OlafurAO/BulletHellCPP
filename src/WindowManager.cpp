#include <WindowManager.h>

bool operator==(const SDL_Color& color1, const SDL_Color& color2) {
  return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}

bool operator!=(const SDL_Color& color1, const SDL_Color& color2) { return !(color1 == color2); }

WindowManager::WindowManager(ResourceManager* resourceManager) {
  _resourceManager = resourceManager;
  _window = nullptr;
}

WindowManager::~WindowManager() {}

void WindowManager::init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags) {
  SDL_Init(SDL_INIT_EVERYTHING);
  _window = SDL_CreateWindow(title, wPosX, wPosY, windowW, windowH, flags);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
  SDL_GetWindowSize(_window, &_screenWidth, &_screenHeight);
  SDL_ShowCursor(SDL_DISABLE);
}

void WindowManager::renderScreen() {
  SDL_SetRenderDrawColor(_renderer, 0, 0, 1, 255);
  SDL_RenderClear(_renderer);
}

void WindowManager::renderGameObjects(std::vector<GameObject*> objs) {
  for (const auto& obj : objs) {
    GameObjectType type = obj->getObjectType();
    SDL_RendererFlip flip =
        obj->getDirection() < 0 ? type == GameObjectType::WEAPON ? SDL_FLIP_VERTICAL : SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    drawGameObject(obj, obj->getZRotation(), flip);

    if (type == GameObjectType::PLAYER) {
      Character* player = dynamic_cast<Character*>(obj);
      SDL_Rect crosshair = player->getCrosshairPosition();

      SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
      SDL_RenderFillRect(_renderer, &crosshair);
    }
  }
}

void WindowManager::renderTexture(SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect, double angle, SDL_RendererFlip flip) {
  SDL_RenderCopyExF(_renderer, texture, &srcRect, &destRect, angle, nullptr, flip);
}

void WindowManager::renderDebugProps(std::vector<Joystick*> joysticks) {
  for (const auto& joystick : joysticks) {
    Texture2D& joystickTexture = _resourceManager->getTexture(joystick->getTextureKey());
    SDL_Rect rect = {100, 100, 200, 200};

    SDL_RenderCopy(_renderer, joystickTexture.getTexture(), &rect, &rect);
  }
}

void WindowManager::drawGameObject(GameObject* obj, double angle, SDL_RendererFlip flip) {
  Texture2D& objTexture = _resourceManager->getTexture(obj->getTextureKey());
  SDL_Rect spriteFrame = objTexture.getSpriteFrame(obj->getSpriteIndex());
  SDL_FRect objPos = obj->getPositionRect();

  SDL_Texture* tex = objTexture.getTexture();
  SDL_Color objColor = obj->getColor();
  bool setColor = objColor != g_DEFAULT_COLOR;

  if (setColor)
    SDL_SetTextureColorMod(tex, objColor.r, objColor.g, objColor.b);

  renderTexture(tex, spriteFrame, objPos, angle, flip);

  if (setColor)
    SDL_SetTextureColorMod(tex, g_DEFAULT_COLOR.r, g_DEFAULT_COLOR.g, g_DEFAULT_COLOR.b);

  // Debug
  SDL_FRect hitbox = obj->getHitboxBounds();
  SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
  SDL_RenderDrawRectF(_renderer, &hitbox);

  // Debug
  glm::vec2 centerPoint = obj->getPositionVec();
  SDL_FRect a = {centerPoint.x - 2.5, centerPoint.y - 2.5, 5, 5};
  SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
  SDL_RenderDrawRectF(_renderer, &a);
}

void WindowManager::presentScreen() { SDL_RenderPresent(_renderer); }

SDL_Renderer* WindowManager::getRenderer() { return _renderer; }

std::pair<int, int> WindowManager::getScreenSize() { return std::pair<int, int>(_screenHeight, _screenWidth); }

void WindowManager::cleanUp() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);

  _resourceManager->cleanUpResources();
  delete _resourceManager;
}
