#include "MainMenu.h"

MainMenu::MainMenu(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow) {
	mWindow = window.lock();
	mRenderWindow = renderWindow;

	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
		windowPtr->setVerticalSyncEnabled(true);
		windowPtr->setKeyRepeatEnabled(false);
	}

	SetupMenu();
}

void MainMenu::SetupMenu() {
	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();

		if (!mFont.loadFromFile("Pixel.ttf")) {
		}

		mMenuText[0].setFont(mFont);
		mMenuText[0].setFillColor(sf::Color::White);
		mMenuText[0].setString("Jugar");
		mMenuText[0].setCharacterSize(50);
		sf::FloatRect textRect = mMenuText[0].getLocalBounds();
		mMenuText[0].setOrigin(textRect.left + textRect.width * .5f, textRect.top + textRect.height / .5f);
		mMenuText[0].setPosition(windowPtr->getSize().x*.5f, 400);

		mMenuText[1].setFont(mFont);
		mMenuText[1].setFillColor(sf::Color::White);
		mMenuText[1].setString("Salir");
		mMenuText[1].setCharacterSize(50);
		textRect = mMenuText[1].getLocalBounds();
		mMenuText[1].setOrigin(textRect.left + textRect.width * .5f, textRect.top + textRect.height / .5f);
		mMenuText[1].setPosition(windowPtr->getSize().x * .5f, 500);

		mButtonPosSelected = -1;
	}
	
}

void MainMenu::HandleInput() {
	sf::Event event;
	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
		while (windowPtr->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mWindow.get()->FinishWindow();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
				mWindow.get()->ToggleFullscreen();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					MoveCursorUp();
					break;
				case sf::Keyboard::S:
					MoveCursorDown();
					break;
				case sf::Keyboard::Enter:
					if (mButtonPosSelected == 0) {
						mHasGameStarted = true;
					}
					else if (mButtonPosSelected == 1) {
						mWindow->FinishWindow();
					}
					break;
				}
			}
		}
	}
}
void MainMenu::Update() {

}

void MainMenu::Render() {
	mWindow->BeginDraw();
	for (int i = 0; i < MAX_MENU_SIZE; ++i) {
		mWindow->Draw(mMenuText[i]);
	}
	mWindow->EndDraw();

	
}

void MainMenu::MoveCursorUp() {
	if (mButtonPosSelected - 1 >= 0) {
		mMenuText[mButtonPosSelected].setFillColor(sf::Color::White);
		std::cout << "Before " << mButtonPosSelected << std::endl;
		mButtonPosSelected--;
		if (mButtonPosSelected < 0) {
			std::cout << "Set to 1 " << std::endl;
			mButtonPosSelected = 1;
		}
		std::cout << "After " << mButtonPosSelected << std::endl;
		mMenuText[mButtonPosSelected].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveCursorDown() {
	if (mButtonPosSelected + 1 <= MAX_MENU_SIZE) {
		mMenuText[mButtonPosSelected].setFillColor(sf::Color::White);

		mButtonPosSelected++;

		if (mButtonPosSelected == 2) {
			mButtonPosSelected = 0;
		}

		mMenuText[mButtonPosSelected].setFillColor(sf::Color::Red);
	}
}