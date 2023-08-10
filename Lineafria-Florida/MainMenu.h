#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "Window.h"

const int MAX_MENU_SIZE = 2;

/************************************
* @class:    MainMenu
* @access:   public
* @brief:    Esta clase se encarga de mostrar y actualizar el menú principal del juego, permitiendo iniciar una partida o salir del juego.
* @details:  Sin detalles.
*************************************/
class MainMenu {
public:
	MainMenu(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow);
	virtual ~MainMenu();

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
	sf::Sprite mBackground;
	sf::Sprite mTitle;
	sf::Texture mBGTexture;
	sf::Texture mTitleTexture;
	std::shared_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	bool mHasGameStarted;
};
