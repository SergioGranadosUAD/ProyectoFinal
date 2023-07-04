#pragma once
#include <iostream>
#include <sfml/Graphics.hpp>
#include <memory>

/************************************
* @class:    Window
* @access:   public
* @brief:    Esta clase contiene la ventana del juego, necesaria para mostrarlo de manera gráfica.
* @details:  Cuenta con una ventana de SFML, elementos relacionados a esta ventana, y métodos para realizar las tareas necesarias para su construcción y dibujo.
*************************************/
class Window {
public:
	Window();
	Window(const std::string& mTitle, const sf::Vector2u& mSize);
	~Window();

	void BeginDraw();
	void EndDraw();

	bool IsDone();
	void FinishWindow();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& mDrawable);

	inline sf::RenderWindow* GetMWindow() { return &mWindow; }
private:
	void Setup(const std::string& mTitle, const sf::Vector2u& mSize);
	void Destroy();
	void Create();

	sf::RenderWindow mWindow;
	sf::Vector2u mWindowSize;
	std::string mWindowTitle;
	bool mIsDone;
	bool mIsFullscreen;
};