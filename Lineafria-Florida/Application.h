#pragma once
#include "Game.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Window.h"
#include <memory>

enum GAME_STATE {
	MENU = 0,
	PLAYING = 1,
	PAUSE = 2
};

class Application {
public:
	Application();
	~Application();
	void HandleInput();
	void Update();
	void Render();

	void RestartClock();

	std::weak_ptr<float> GetElapsed();
	std::weak_ptr<Window> GetWindow();

private:
	std::shared_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	sf::Clock mClock;
	std::shared_ptr<float> mElapsed;
	GAME_STATE mState;
	std::unique_ptr<Game> mGame;
	std::unique_ptr<MainMenu> mMainMenu;
};