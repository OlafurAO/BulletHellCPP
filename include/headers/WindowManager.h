#include <fstream>
#include <sstream>
#include <vector>

#include <sdl2/SDL.h>

#include <Enums.h>
#include <GameObject.h>
#include <ResourceManager.h>

class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void init(const char* title, int wPosX, int wPosY, int windowW, int windowH, Uint32 flags);

  void renderScreen(std::vector<GameObject*> gameObjects);
  void renderGameObjects(std::vector<GameObject*> gameObjects);

  void cleanUp();

  void initTexture(const char* imgPath, const char* texKey, TextureType texType, int spriteRows = 0, int spriteCols = 0);

private:
  SDL_Window* _window;
  SDL_Renderer* _renderer;

  const float _aspectRatio = 16.f / 9.f;

  ResourceManager* _resourceManager;
};
