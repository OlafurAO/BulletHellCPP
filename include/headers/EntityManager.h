#pragma once

#include <vector>

#include <AudioManager.h>
#include <Character.h>
#include <Enemy.h>
#include <GameObject.h>
#include <Item.h>
#include <Path.h>
#include <Player.h>
#include <Projectile.h>
#include <ResourceManager.h>
#include <Weapon.h>

class EntityManager {
public:
  EntityManager(ResourceManager* resourceManager, AudioManager* audioManager);
  ~EntityManager();

  // TODO: have some sort of entity blueprint?
  void initEntities();

  void updateEntities(double deltaTime);

  Player*& getPlayer();

  std::vector<GameObject*> getAllGameObjects();

private:
  ResourceManager* _resourceManager;
  AudioManager* _audioManager;

  Player* _player;

  std::vector<Character*> _characters;
  std::vector<Weapon*> _weapons;
  std::vector<Projectile*> _projectiles;
  std::vector<Item*> _items;
};
