#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Window.h"

class HUD {
public:
	HUD(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow, std::weak_ptr<sf::View> view, const unsigned int& ammoCount);
	virtual ~HUD();

	void Update();
	void Render();

	void SubstractBullet();
	void ReloadWeapon();
private:
	std::weak_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	std::weak_ptr<sf::View> mView;
	sf::Sprite mCrosshair;
	sf::Sprite mPistol;
	sf::Texture mCrosshairTex;
	sf::Texture mPistolTex;
	sf::Text mAmmunition;
	sf::Font mFont;
	unsigned int mMaxAmmo;
	unsigned int mAmmoCount;
};