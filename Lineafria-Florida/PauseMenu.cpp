#include "PauseMenu.h"

/************************************
* @method:   MainMenu
* @access:   public
* @return:   void
* @brief:    Constructor de la clase MainMenu.
* @details:  Sin detalles.
*************************************/
PauseMenu::PauseMenu(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow) {
	mWindow = window;
	mRenderWindow = renderWindow;
	mIsGameResumed = true;
	mGameFinished = false;

	SetupMenu();
}

/************************************
* @method:   ~MainMenu
* @access:   public
* @return:   void
* @brief:    Destructor de MainMenu
* @details:  Sin detalles.
*************************************/
PauseMenu::~PauseMenu() {

}

/************************************
* @method:   SetupMenu
* @access:   public
* @return:   void
* @brief:    Este método carga y asigna la información necesaria a todos los elementos en el menú.
* @details:  Sin detalles.
*************************************/
void PauseMenu::SetupMenu() {
	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();

		if (!mFont.loadFromFile("Pixel.ttf")) {
		}
		sf::Vector2u windowSize = windowPtr->getSize();
		mBackground.setSize(sf::Vector2f(windowSize.x, windowSize.y));
		mBackground.setOrigin(sf::Vector2f(windowSize.x * .5f, windowSize.y * .5f));
		mBackground.setPosition(sf::Vector2f(windowSize.x * .75f, windowSize.y * .75f));
		mBackground.setFillColor(sf::Color(0, 0, 0, 200));

		mMenuText[0].setFont(mFont);
		mMenuText[0].setFillColor(sf::Color::Red);
		mMenuText[0].setString("Continuar");
		mMenuText[0].setCharacterSize(20);
		sf::FloatRect textRect = mMenuText[0].getLocalBounds();
		mMenuText[0].setOrigin(0.f, textRect.top + textRect.height / .5f);
		mMenuText[0].setPosition(450, 400);

		mMenuText[1].setFont(mFont);
		mMenuText[1].setFillColor(sf::Color::White);
		mMenuText[1].setString("Salir");
		mMenuText[1].setCharacterSize(20);
		textRect = mMenuText[1].getLocalBounds();
		mMenuText[1].setOrigin(0.f, textRect.top + textRect.height / .5f);
		mMenuText[1].setPosition(450, 450);

		mButtonPosSelected = 0;
	}

}

/************************************
* @method:   HandleInput
* @access:   public
* @return:   void
* @brief:    Método que recibe la entrada del usuario. Permite navegar en el menú.
* @details:  Sin detalles.
*************************************/
void PauseMenu::HandleInput() {
	sf::Event event;
	if (!mRenderWindow.expired() && !mWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> renderWindowPtr = mRenderWindow.lock();
		std::shared_ptr<Window> windowPtr = mWindow.lock();
		while (renderWindowPtr->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				windowPtr->FinishWindow();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
				windowPtr->ToggleFullscreen();
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
						mIsGameResumed = true;
					}
					else if (mButtonPosSelected == 1) {
						mGameFinished = true;
					}
					break;
				case sf::Keyboard::Escape:
					mIsGameResumed = true;
				}
			}
		}
	}
}

/************************************
* @method:   Update
* @access:   public
* @return:   void
* @brief:    Método que actualiza el menú cada frame. Sin uso por falta de implementación de animaciones.
* @details:  Sin detalles.
*************************************/
void PauseMenu::Update() {

}

/************************************
* @method:   Render
* @access:   public
* @return:   void
* @brief:    Método que dibuja todos los elementos del menú en la pantalla.
* @details:  Sin detalles.
*************************************/
void PauseMenu::Render() {
	if (!mWindow.expired()) {
		std::shared_ptr<Window> windowPtr = mWindow.lock();
		windowPtr->Draw(mBackground);
		for (int i = 0; i < MAX_PAUSEMENU_SIZE; ++i) {
			windowPtr->Draw(mMenuText[i]);
		}
	}
	
}

/************************************
* @method:   MoveCursorUp
* @access:   public
* @return:   void
* @brief:    Este método selecciona el botón de arriba al presionar la tecla correspondiente.
* @details:  Sin detalles.
*************************************/
void PauseMenu::MoveCursorUp() {
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

/************************************
* @method:   MoveCursorDown
* @access:   public
* @return:   void
* @brief:    Este método selecciona el botón de abajo al presionar la tecla correspondiente.
* @details:  Sin detalles.
*************************************/
void PauseMenu::MoveCursorDown() {
	if (mButtonPosSelected + 1 <= MAX_PAUSEMENU_SIZE) {
		mMenuText[mButtonPosSelected].setFillColor(sf::Color::White);

		mButtonPosSelected++;

		if (mButtonPosSelected == 2) {
			mButtonPosSelected = 0;
		}

		mMenuText[mButtonPosSelected].setFillColor(sf::Color::Red);
	}
}

/************************************
* @method:   PauseGame
* @access:   public
* @return:   void
* @brief:    Este método le indica al menú que el juego está en estado de pausa.
* @details:  Sin detalles.
*************************************/
void PauseMenu::PauseGame() {
	mIsGameResumed = false;
}

/************************************
* @method:   CenterElements
* @access:   public
* @return:   void
* @brief:    Este método mantiene a los elementos del menú centrados a la pantalla.
* @details:  Sin detalles.
*************************************/
void PauseMenu::CenterElements(const sf::Vector2f& viewPos) {
	mBackground.setPosition(viewPos);
	mMenuText[0].setPosition(viewPos.x-250, viewPos.y + 25);
	mMenuText[1].setPosition(viewPos.x-250, viewPos.y + 65);
}