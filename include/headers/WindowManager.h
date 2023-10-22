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
  void drawGameObject(GameObject* obj);

  void cleanUp();

  SDL_Renderer* getRenderer();
  Texture2D& initTexture(const char* imgPath, const char* texKey, TextureType texType, int spriteRows = 0, int spriteCols = 0);

private:
  SDL_Window* _window;
  SDL_Renderer* _renderer;

  const float _aspectRatio = 16.f / 9.f;

  ResourceManager* _resourceManager;
};
