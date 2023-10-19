#include <WindowManager.h>

WindowManager::WindowManager() {
  _window = nullptr;
  _resourceManager = new ResourceManager();
}

WindowManager::~WindowManager() {}

void WindowManager::init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags) {
  SDL_Init(SDL_INIT_EVERYTHING);
  _window = SDL_CreateWindow(title, wPosX, wPosY, windowW, windowH, flags);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void WindowManager::renderScreen(std::vector<GameObject*> gameObjects) {
  SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
  SDL_RenderClear(_renderer);
  renderGameObjects(gameObjects);
  SDL_RenderPresent(_renderer);
}

void WindowManager::renderGameObjects(std::vector<GameObject*> gameObjects) {
  SDL_Rect a;
  a.x = 100;
  a.y = 100;
  a.w = 200;
  a.h = 100;

  // SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
  // SDL_RenderFillRect(_renderer, &a);

  for (const auto& obj : gameObjects) {
    Texture2D& objTexture = _resourceManager->getTexture(obj->getTextureKey());

    SDL_Rect objPos = obj->getPositionRect();
    SDL_Rect spriteFrame = objTexture.getSpriteFrame(obj->getSpriteIndex());

    SDL_RenderCopyEx(_renderer, objTexture.getTexture(), &spriteFrame, &objPos, 0.f, nullptr,
                     obj->getDirection() > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
  }
}

void WindowManager::initTexture(const char* imgPath, const char* texKey, TextureType texType, int spriteRows, int spriteCols) {
  _resourceManager->loadTexture(_renderer, imgPath, texKey, texType, spriteRows, spriteCols);
}

void WindowManager::cleanUp() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);

  _resourceManager->cleanUpResources();
  delete _resourceManager;
}
