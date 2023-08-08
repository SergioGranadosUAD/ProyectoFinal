#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "Window.h"

const int MAX_PAUSEMENU_SIZE = 2;

class PauseMenu {
public:
	PauseMenu(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow);
	virtual ~PauseMenu();

	void HandleInput();
	void Update();
	void Render();

	void SetupMenu();
	void MoveCursorUp();
	void MoveCursorDown();

	void PauseGame();
	void CenterElements(const sf::Vector2f& viewPos);

	inline int ButtonSelected() const  { return mButtonPosSelected; }

	inline bool GameResumed() const { return mIsGameResumed; }
	inline bool GameFinished() const { return mGameFinished; }
private:
	int mButtonPosSelected;
	bool mIsGameResumed;
	bool mGameFinished;
	sf::Font mFont;
	sf::Text mMenuText[MAX_PAUSEMENU_SIZE];
	sf::RectangleShape mBackground;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	std::weak_ptr<Window> mWindow;
};
