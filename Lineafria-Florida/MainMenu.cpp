#include "MainMenu.h"

/************************************
* @method:   MainMenu
* @access:   public
* @return:   void
* @brief:    Constructor de la clase MainMenu.
* @details:  Sin detalles.
*************************************/
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

/************************************
* @method:   ~MainMenu
* @access:   public
* @return:   void
* @brief:    Destructor de MainMenu
* @details:  Sin detalles.
*************************************/
MainMenu::~MainMenu() {

}

/************************************
* @method:   SetupMenu
* @access:   public
* @return:   void
* @brief:    Este método carga y asigna la información necesaria a todos los elementos en el menú.
* @details:  Sin detalles.
*************************************/
void MainMenu::SetupMenu() {
	if (!mRenderWindow.expired()) {
		std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();

		if (!mFont.loadFromFile("Pixel.ttf")) {
		}

		if (!mBGTexture.loadFromFile("Resources/MenuBG.jpg")) {

		}

		if (!mTitleTexture.loadFromFile("Resources/GraphicDesignIsMyPassion.png")) {

		}

		mBackground.setTexture(mBGTexture);
		mBackground.setScale(.75f, .75f);

		mTitle.setTexture(mTitleTexture);
		sf::FloatRect titleRect = mTitle.getLocalBounds();
		mTitle.setOrigin(titleRect.left + titleRect.width * .5f, titleRect.top + titleRect.height * .5f);
		mTitle.setPosition(windowPtr->getSize().x * .5f, 250);


		mMenuText[0].setFont(mFont);
		mMenuText[0].setFillColor(sf::Color::Red);
		mMenuText[0].setString("Jugar");
		mMenuText[0].setCharacterSize(50);
		sf::FloatRect textRect = mMenuText[0].getLocalBounds();
		mMenuText[0].setOrigin(textRect.left + textRect.width * .5f, textRect.top + textRect.height * .5f);
		mMenuText[0].setPosition(windowPtr->getSize().x*.5f, 500);

		mMenuText[1].setFont(mFont);
		mMenuText[1].setFillColor(sf::Color::White);
		mMenuText[1].setString("Salir");
		mMenuText[1].setCharacterSize(50);
		textRect = mMenuText[1].getLocalBounds();
		mMenuText[1].setOrigin(textRect.left + textRect.width * .5f, textRect.top + textRect.height * .5f);
		mMenuText[1].setPosition(windowPtr->getSize().x * .5f, 600);

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

/************************************
* @method:   Update
* @access:   public
* @return:   void
* @brief:    Método que actualiza el menú cada frame. Sin uso por falta de implementación de animaciones.
* @details:  Sin detalles.
*************************************/
void MainMenu::Update() {

}

/************************************
* @method:   Render
* @access:   public
* @return:   void
* @brief:    Método que dibuja todos los elementos del menú en la pantalla.
* @details:  Sin detalles.
*************************************/
void MainMenu::Render() {
	mWindow->BeginDraw();
	mWindow->Draw(mBackground);
	mWindow->Draw(mTitle);
	for (int i = 0; i < MAX_MENU_SIZE; ++i) {
		mWindow->Draw(mMenuText[i]);
	}
	mWindow->EndDraw();
}

/************************************
* @method:   MoveCursorUp
* @access:   public
* @return:   void
* @brief:    Este método selecciona el botón de arriba al presionar la tecla correspondiente.
* @details:  Sin detalles.
*************************************/
void MainMenu::MoveCursorUp() {
	if (mButtonPosSelected - 1 >= 0) {
		mMenuText[mButtonPosSelected].setFillColor(sf::Color::White);
		mButtonPosSelected--;
		if (mButtonPosSelected < 0) {
			mButtonPosSelected = 1;
		}
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