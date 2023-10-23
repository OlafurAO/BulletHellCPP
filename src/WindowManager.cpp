#include <WindowManager.h>

bool operator==(const SDL_Color& color1, const SDL_Color& color2) {
  return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}

bool operator!=(const SDL_Color& color1, const SDL_Color& color2) { return !(color1 == color2); }

WindowManager::WindowManager() {
  _window = nullptr;
  _resourceManager = new ResourceManager();
}

WindowManager::~WindowManager() {}

void WindowManager::init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags) {
  SDL_Init(SDL_INIT_EVERYTHING);
  _window = SDL_CreateWindow(title, wPosX, wPosY, windowW, windowH, flags);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

void WindowManager::renderScreen() {
  SDL_SetRenderDrawColor(_renderer, 0, 0, 1, 255);
  SDL_RenderClear(_renderer);
}

void WindowManager::renderGameObjects(std::vector<Character*> characters, std::vector<Item*> items) {
  for (const auto& character : characters) {
    drawGameObject(character);

    GameObject* equippedWeapon = character->getEquippedWeapon();
    if (equippedWeapon != nullptr) {
      drawGameObject(equippedWeapon);
    }
  }

  for (const auto& item : items) {
    drawGameObject(item);
  }
}

void WindowManager::renderTexture(SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect, int direction) {
  SDL_RenderCopyExF(_renderer, texture, &srcRect, &destRect, 0.f, nullptr, direction > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void WindowManager::renderDebugProps(std::vector<Joystick*> joysticks) {
  for (const auto& joystick : joysticks) {
    Texture2D& joystickTexture = _resourceManager->getTexture(joystick->getTextureKey());
    SDL_Rect rect = {100, 100, 200, 200};

    SDL_RenderCopy(_renderer, joystickTexture.getTexture(), &rect, &rect);
  }
}

void WindowManager::drawGameObject(GameObject* obj, SDL_Color color) {
  Texture2D& objTexture = _resourceManager->getTexture(obj->getTextureKey());
  SDL_Rect spriteFrame = objTexture.getSpriteFrame(obj->getSpriteIndex());
  SDL_FRect objPos = obj->getPositionRect();

  SDL_Texture* tex = objTexture.getTexture();
  SDL_Color objColor = obj->getColor();
  bool setColor = objColor != g_DEFAULT_COLOR;

  if (setColor)
    SDL_SetTextureColorMod(tex, objColor.r, objColor.g, objColor.b);

  renderTexture(tex, spriteFrame, objPos, obj->getDirection());

  if (setColor)
    SDL_SetTextureColorMod(tex, g_DEFAULT_COLOR.r, g_DEFAULT_COLOR.g, g_DEFAULT_COLOR.b);

  // Debug
  SDL_FRect hitbox = obj->getHitboxBounds();
  SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
  SDL_RenderDrawRectF(_renderer, &hitbox);
}

void WindowManager::presentScreen() { SDL_RenderPresent(_renderer); }

SDL_Renderer* WindowManager::getRenderer() { return _renderer; }

Texture2D& WindowManager::initTexture(const char* imgPath, const char* texKey, TextureType texType, int spriteRows, int spriteCols) {
  return _resourceManager->loadTexture(_renderer, imgPath, texKey, texType, spriteRows, spriteCols);
}

void WindowManager::cleanUp() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);

  _resourceManager->cleanUpResources();
  delete _resourceManager;
}
