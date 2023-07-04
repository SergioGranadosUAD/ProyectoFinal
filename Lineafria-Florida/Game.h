#pragma once
#include <memory>
#include <vector>
#include "Window.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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

/************************************
* @class:    Game
* @access:   public
* @brief:    Esta clase contiene la base del juego, con todos los métodos necesarios para su funcionamiento.
* @details:  Cuenta con una referencia a la ventana de juego, un jugador único, un reloj interno con su diferencia en tiempo, así como una lista de
*			 enemigos y proyectiles.
*************************************/
class Game {
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	void RestartClock();
	void CheckProjectileCollision();
	void RestartGame();

	float GetElapsed();
	std::weak_ptr<Window> GetWindow();

private:
	std::shared_ptr<Window> mWindow;
	std::unique_ptr<Player> mPlayer;
	sf::Clock mClock;
	float mElapsed;
	AnimFlags animFlags;
	std::vector<std::shared_ptr<Bullet>> projectiles;
	std::vector<std::shared_ptr<Enemy>> enemies;

};