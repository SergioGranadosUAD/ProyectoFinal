#pragma once
#include <memory>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "Window.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "HUD.h"

using nlohmann::json;

/************************************
* @class:    AnimFlags
* @access:   public
* @brief:    Este struct se ocupa para tener los cuatro estados de movimiento que puede recibir el jugador.
* @details:  Sin detalles.
*************************************/
struct AnimFlags {
	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
};

struct LevelData {
	sf::Vector2f spawnPos;
	int width = 0;
	int height = 0;
	std::vector<int> layerTiles;
	std::vector<int> layerWalls;
	std::vector<sf::RectangleShape> layerWallsCol;
};

/************************************
* @class:    Game
* @access:   public
* @brief:    Esta clase contiene la base del juego, con todos los métodos necesarios para su funcionamiento.
* @details:  Cuenta con una referencia a la ventana de juego, un jugador único, un reloj interno con su diferencia en tiempo, así como una lista de
*			 enemigos y proyectiles.
*************************************/
class Game {
public:
	Game(std::weak_ptr<Window> window, std::weak_ptr<float> elapsed, const std::string& levelname);
	virtual ~Game();

	void HandleInput();
	void Update();
	void Render();
	void RestartClock();
	void CheckProjectileCollision();
	void CheckPlayerCollisions(std::shared_ptr<sf::RectangleShape> wall);
	void CheckEnemyCollisions(std::shared_ptr<Enemy> enemy, std::shared_ptr<sf::RectangleShape> wall);
	void CheckEnemyOnEnemyCollisions(std::shared_ptr<Enemy> enemy1, std::shared_ptr<Enemy> enemy2);
	void ChangeLevel(const std::string& levelName);
	void ResetView();
	LevelData LoadLevel(const std::string& levelName);

	std::weak_ptr<float> GetElapsed();
	std::weak_ptr<Window> GetWindow();

	inline bool GameFinished() const { return mGameFinished; }

private:
	std::shared_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	std::unique_ptr<Player> mPlayer;
	std::shared_ptr<sf::View> mView;
	std::unique_ptr<PauseMenu> mPauseMenu;
	std::unique_ptr<TileMap> mFloorLayer;
	std::unique_ptr<TileMap> mWallLayer;
	std::unique_ptr<HUD> mHud;
	sf::Clock mClock;
	std::shared_ptr<float> mElapsed;
	AnimFlags animFlags;
	std::vector<std::shared_ptr<Bullet>> projectiles;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<sf::RectangleShape>> mWallCollisions;
	std::unique_ptr<sf::RectangleShape> mNextLevelZone;
	bool mWinCondition;
	bool mGameFinished;

	std::string mCurrentLevelName;
	std::string mNextLevelName;
};