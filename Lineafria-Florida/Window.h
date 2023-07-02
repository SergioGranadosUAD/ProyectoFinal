#pragma once
#include <iostream>
#include <sfml/Graphics.hpp>
#include <memory>

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