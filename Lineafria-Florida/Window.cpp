#include "Window.h"

Window::Window() {
	Setup("Game Window", sf::Vector2u(800, 600));
}

Window::Window(const std::string& mTitle, const sf::Vector2u& mSize) {
	Setup(mTitle, mSize);
}

Window::~Window() {
	Destroy();
}

void Window::Setup(const std::string& mTitle, const sf::Vector2u& mSize) {
	mWindowTitle = mTitle;
	mWindowSize = mSize;
	mIsFullscreen = false;
	mIsDone = false;
	Create();
}

void Window::Create() {
	sf::Uint32 windowStyle = (mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	mWindow.create({ mWindowSize.x, mWindowSize.y, 32 }, mWindowTitle, windowStyle);
}

void Window::Destroy() {
	mWindow.close();
}

void Window::FinishWindow() {
	mIsDone = true;
}

void Window::ToggleFullscreen() {
	mIsFullscreen = !mIsFullscreen;
	Destroy();
	Create();
}

void Window::BeginDraw() {
	mWindow.clear();
}

void Window::EndDraw() {
	mWindow.display();
}

bool Window::IsDone() {
	return mIsDone;
}

bool Window::IsFullscreen() {
	return mIsFullscreen;
}

sf::Vector2u Window::GetWindowSize() {
	return mWindowSize;
}

void Window::Draw(sf::Drawable& mDrawable) {
	mWindow.draw(mDrawable);
}