#include <headers/Game.h>

// watch this for setup: https://www.youtube.com/watch?v=9Ca-RVPwnBE
int main(int argc, char* argv[]) {
  const char* gameTitle = "Game";
  const int screenWidth = 1800;
  const int screenHeight = 860;

  Game game = Game();
  game.init(gameTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
  game.run();

  return 0;
}
