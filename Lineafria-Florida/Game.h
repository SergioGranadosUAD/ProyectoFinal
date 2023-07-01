#pragma once
#include "Window.h"
#include "Player.h"
#include "Bullet.h"

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

	float GetElapsed();
	Window* GetWindow();

private:
	Window mWindow;
	Player mPlayer;
	sf::Clock mClock;
	float mElapsed;
	AnimFlags animFlags;
	std::vector<Bullet*> projectiles;
};