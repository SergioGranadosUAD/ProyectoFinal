#pragma once
#include <memory>
#include <vector>
#include "Window.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

struct AnimFlags {
	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
};

class Game {
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	void RestartClock();

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

	//ToRemove
	int timer2s;
};