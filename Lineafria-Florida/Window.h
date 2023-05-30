#pragma once
#include <iostream>
#include <sfml/Graphics.hpp>

class Window {
public:
	Window();
	Window(const std::string& mTitle, const sf::Vector2u& mSize);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& mDrawable);
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