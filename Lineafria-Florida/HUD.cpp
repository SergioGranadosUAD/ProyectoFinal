#include "HUD.h"

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

HUD::~HUD() {

}

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

void HUD::Render() {
	if (!mWindow.expired()) {
		std::shared_ptr<Window> windowPtr = mWindow.lock();

		windowPtr->Draw(mCrosshair);
		windowPtr->Draw(mPistol);
		windowPtr->Draw(mAmmunition);
	}
	
}

void HUD::SubstractBullet() {
	mAmmoCount--;
	if (mAmmoCount == 0) {
		mAmmunition.setString("- / " + std::to_string(mMaxAmmo));
	}
	else {
		mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
	}
}

void HUD::ReloadWeapon() {
	mAmmoCount = mMaxAmmo;
	mAmmunition.setString(std::to_string(mAmmoCount) + " / " + std::to_string(mMaxAmmo));
}