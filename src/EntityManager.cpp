#include <EntityManager.h>

EntityManager::EntityManager(ResourceManager* resourceManager, AudioManager* audioManager) {
  _resourceManager = resourceManager;
  _audioManager = audioManager;
  _player = nullptr;
}

EntityManager::~EntityManager() {
  _characters.clear();
  _weapons.clear();
  _projectiles.clear();
  _items.clear();
}

void EntityManager::initEntities() {
  //////////////////////////////////////////////////////////////
  // initCharacter(GameObjectType objectType, float scale, float speed, Path texPath, texKey, spriteCols, spriteRows)

  _player = new Player(GameObjectType::PLAYER, 1.f, 0.2f);
  _player->initAudioManager(_audioManager);

  const char* textureKey = "player";
  Texture2D& playerTex =
      _resourceManager->loadTexture(Path("player.png", ResType::SPRITE_CHAR), textureKey, TextureType::SPRITESHEET, 10, 6);
  _player->registerTexture(textureKey, playerTex, _resourceManager->getRenderer(), 0);

  _player->initAnimator();
  _player->registerAnimation(AnimationType::IDLE1, new int[6]{6, 7, 8, 9, 10, 11}, 6, true);
  _player->registerAnimation(AnimationType::WALK1, new int[6]{24, 25, 26, 27, 28, 29}, 6, true);

  _player->playAnimation(AnimationType::IDLE1);

  Enemy* enemy = new Enemy(GameObjectType::ENEMY, 4000.f, 2500.f, 0.75f, 0.1f);
  enemy->initAudioManager(_audioManager);

  const char* textureKey2 = "slime";
  Texture2D& slimeTex = _resourceManager->loadTexture(Path("slime.png", ResType::SPRITE_CHAR), textureKey2, TextureType::SPRITESHEET, 5, 7);
  enemy->registerTexture(textureKey2, slimeTex, _resourceManager->getRenderer(), 2);

  enemy->initAnimator();
  enemy->registerAnimation(AnimationType::IDLE1, new int[4]{0, 1, 2, 3}, 4, true);
  enemy->playAnimation(AnimationType::IDLE1);

  _characters.push_back(_player);
  _characters.push_back(enemy);

  const char* gunsTexKey = "weapons_guns";
  const char* bulletTexKey = "weapons_bullet";
  Texture2D& gunTex =
      _resourceManager->loadTexture(Path("revolver.png", ResType::SPRITE_WEAPONS), gunsTexKey, TextureType::SPRITESHEET, 1, 1);
  Texture2D& bulletTex =
      _resourceManager->loadTexture(Path("AK47.png", ResType::SPRITE_WEAPONS), bulletTexKey, TextureType::SPRITESHEET, 1, 1);

  Weapon* revolver = new Weapon(GameObjectType::WEAPON, 0.25f);
  revolver->initBaselineProjectile();

  revolver->registerTexture(gunsTexKey, gunTex, _resourceManager->getRenderer(), 0);
  revolver->registerProjectileTexture(bulletTexKey, bulletTex, _resourceManager->getRenderer(), 0);
  _player->equipWeapon(revolver);

  _weapons.push_back(revolver);
  /////////////////////////////////////////////////////////
}

void EntityManager::updateEntities(double deltaTime) {
  // FIXME: need to access all projectiles, of equipped weapons, weapons in inventory and recently discarded weapons
  // TODO: garbage clean projectiles
  // TODO: garbage clean discarded weapons once all of its projectiles have been deleted
  for (const auto& character : _characters) {
    if (character->getObjectType() == GameObjectType::ENEMY) {
      Enemy* enemy = dynamic_cast<Enemy*>(character);
      if (enemy != nullptr) {
        // enemy->update(_player, deltaTime);
      }
    } else if (character->getObjectType() == GameObjectType::PLAYER) {
      Player* player = dynamic_cast<Player*>(character);
      if (player != nullptr) {
        // player->update();
      }
    }

    character->update(deltaTime);

    // FIXME: Have characters be immune to own projectiles lol
    // TODO: check projectile collision
    // character->checkProjectileCollision(_projectiles);

    GameObject* obj = dynamic_cast<GameObject*>(character);
    if (obj != nullptr) {
      obj->update(deltaTime);
    }
  }

  /*
  for (const auto& weapon : _weapons) {
    std::vector<Projectile*> newProjectiles = weapon->getNewProjectiles();
    if (newProjectiles.size() > 0) {
      _projectiles.insert(_projectiles.end(), newProjectiles.begin(), newProjectiles.end());
      weapon->clearProjectileQueue();
    }
  }*/
}

Player*& EntityManager::getPlayer() { return _player; }

std::vector<GameObject*> EntityManager::getAllGameObjects() {
  std::vector<GameObject*> allObjs;

  for (const auto& character : _characters) {
    allObjs.push_back(character);
  }

  for (const auto& weapon : _weapons) {
    allObjs.push_back(weapon);
  }

  for (const auto& projectile : _projectiles) {
    allObjs.push_back(projectile);
  }

  for (const auto& item : _items) {
    allObjs.push_back(item);
  }

  return allObjs;
}
