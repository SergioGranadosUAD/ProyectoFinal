#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "Window.h"

const int MAX_MENU_SIZE = 2;

class MainMenu {
public:
	MainMenu(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow);

	void HandleInput();
	void Update();
	void Render();

	void SetupMenu();
	void MoveCursorUp();
	void MoveCursorDown();

	inline int ButtonSelected() { return mButtonPosSelected; }

	inline bool GameStarted() { return mHasGameStarted; }

private:
	int mButtonPosSelected;
	sf::Font mFont;
	sf::Text mMenuText[MAX_MENU_SIZE];
	std::shared_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	bool mHasGameStarted;
};
