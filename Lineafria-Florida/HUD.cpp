#include "HUD.h"

/************************************
* @method:   HUD
* @access:   public
* @return:   void
* @brief:    Constructor de la clase HUD. Establece la información de los elementos que se mostrarán en la pantalla.
* @details:  Sin detalles.
*************************************/
HUD::HUD(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow, std::weak_ptr<sf::View> view, const unsigned int& ammoCount) {
	mWindow = window;
	mRenderWindow = renderWindow;
	mView = view;
	mMaxAmmo = ammoCount;
	mAmmoCount = mMaxAmmo;

	if (!mView.expired() && !mRenderWindow.expired()) {
		std::shared_ptr<sf::View> viewPtr = mView.lock();
		std::shared_ptr<sf::RenderWindow> renderPtr = mRenderWindow.lock();

		if (!mFont.loadFromFile("Pixel.ttf")) {
		}

		if (!mCrosshairTex.loadFromFile("Resources/HudCrosshair.png")) {

		}

		if (!mPistolTex.loadFromFile("Resources/HudPistol.png")) {

		}

		if (!mCrosshairReloadTex.loadFromFile("Resources/HudCrosshairReload.png")) {

		}

		mCrosshair.setTexture(mCrosshairTex);
		mPistol.setTexture(mPistolTex);
		sf::FloatRect crosshairSpriteSize = mCrosshair.getGlobalBounds();
		mCrosshair.setOrigin(crosshairSpriteSize.width * .5f, crosshairSpriteSize.height * .5f);
		sf::FloatRect pistolSpriteSize = mPistol.getGlobalBounds();
		mPistol.setOrigin(pistolSpriteSize.width * .5f, pistolSpriteSize.height * .5f);
		mCrosshair.setScale(.75f, .75f);
		mPistol.setScale(2.0f, 2.0f);

		sf::Vector2f viewPos = viewPtr->getCenter();

		mAmmunition.setFont(mFont);
		mAmmunition.setFillColor(sf::Color::White);
		mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
		mAmmunition.setCharacterSize(10);
		sf::FloatRect textRect = mAmmunition.getLocalBounds();
		mAmmunition.setOrigin(textRect.width, textRect.height);

		mAmmunition.setPosition(viewPos.x + 250, viewPos.y + 150);
		mCrosshair.setPosition(renderPtr->mapPixelToCoords(sf::Mouse::getPosition(*renderPtr)));
		mPistol.setPosition(viewPos.x + 232, viewPos.y + 115);
	}
}

/************************************
* @method:   ~HUD
* @access:   public
* @return:   void
* @brief:    Destructor de la clase HUD.
* @details:  Sin detalles.
*************************************/
HUD::~HUD() {

}

/************************************
* @method:   Update
* @access:   public
* @return:   void
* @brief:    Este método actualiza todos los elementos de la interfaz, manteniendo su posición estable de forma relativa al view.
* @details:  Sin detalles.
*************************************/
void HUD::Update() {
	if (!mView.expired() && !mRenderWindow.expired()) {
		std::shared_ptr<sf::View> viewPtr = mView.lock();
		std::shared_ptr<sf::RenderWindow> renderPtr = mRenderWindow.lock();
		sf::Vector2f viewPos = viewPtr->getCenter();
		mAmmunition.setPosition(viewPos.x + 255, viewPos.y + 140);
		mCrosshair.setPosition(renderPtr->mapPixelToCoords(sf::Mouse::getPosition(*renderPtr)));
		mPistol.setPosition(viewPos.x + 232, viewPos.y + 115);
	}
}

/************************************
* @method:   Render
* @access:   public
* @return:   void
* @brief:    Este método dibuja todos los elementos de la interfaz en la pantalla.
* @details:  Sin detalles.
*************************************/
void HUD::Render() {
	if (!mWindow.expired()) {
		std::shared_ptr<Window> windowPtr = mWindow.lock();

		windowPtr->Draw(mCrosshair);
		windowPtr->Draw(mPistol);
		windowPtr->Draw(mAmmunition);
	}
	
}

/************************************
* @method:   SubstractBullet
* @access:   public
* @return:   void
* @brief:    Este método le resta una bala al conteo de balas y lo muestra en el elemento correspondiente de la interfaz.
* @details:  Sin detalles.
*************************************/
void HUD::SubstractBullet() {
	mAmmoCount--;
	if (mAmmoCount == 0) {
		mAmmunition.setString("- / " + std::to_string(mMaxAmmo));
		mCrosshair.setTexture(mCrosshairReloadTex);
	}
	else {
		mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
	}
}

/************************************
* @method:   ReloadWeapon
* @access:   public
* @return:   void
* @brief:    Este método vuelve a establecer el conteo de balas a su valor inicial y actualiza los elementos para reflejar este cambio.
* @details:  Sin detalles.
*************************************/
void HUD::ReloadWeapon() {
	mAmmoCount = mMaxAmmo;
	mCrosshair.setTexture(mCrosshairTex);
	mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
}

/************************************
* @method:   SetAmmunition
* @access:   public
* @return:   void
* @brief:    Este método establece el conteo de balas al valor introducido y actualiza los elementos para reflejar este cambio.
* @details:  Sin detalles.
*************************************/
void HUD::SetAmmunition(const int& ammo) {
	mAmmoCount = ammo;
	if (mAmmoCount == 0) {
		mAmmunition.setString("- / " + std::to_string(mMaxAmmo));
		mCrosshair.setTexture(mCrosshairReloadTex);
	}
	else {
		mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
	}
}