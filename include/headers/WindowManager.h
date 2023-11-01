#include <fstream>
#include <sstream>
#include <vector>

#include <sdl2/SDL.h>

#include <Character.h>
#include <Enums.h>
#include <GameObject.h>
#include <Item.h>
#include <Joystick.h>
#include <ResourceManager.h>
#include <Texture2D.h>

class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags);

  void renderScreen();
  void presentScreen();

  void renderGameObjects(std::vector<Character*> characters, std::vector<Item*> items);
  void renderDebugProps(std::vector<Joystick*> joysticks);
  void renderTexture(SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void drawGameObject(GameObject* obj, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void cleanUp();

  Texture2D& initTexture(const char* imgPath, const char* texKey, TextureType texType, int spriteRows = 0, int spriteCols = 0);
  SDL_Renderer* getRenderer();
  std::pair<int, int> getScreenSize();

private:
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  ResourceManager* _resourceManager;

  const float _ASPECT_RATIO = 16.f / 9.f;

  int _screenWidth, _screenHeight;
};
