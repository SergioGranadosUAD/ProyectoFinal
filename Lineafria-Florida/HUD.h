#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Window.h"

/************************************
* @class:    HUD
* @access:   public
* @brief:    Esta clase se encarga de mostrar y actualizar los elementos del HUD en la pantalla.
* @details:  Sin detalles.
*************************************/
class HUD {
public:
	HUD(std::weak_ptr<Window> window, std::weak_ptr<sf::RenderWindow> renderWindow, std::weak_ptr<sf::View> view, const unsigned int& ammoCount);
	virtual ~HUD();

	void Update();
	void Render();

	void SubstractBullet();
	void ReloadWeapon();
	void SetAmmunition(const int& ammo);
private:
	std::weak_ptr<Window> mWindow;
	std::weak_ptr<sf::RenderWindow> mRenderWindow;
	std::weak_ptr<sf::View> mView;
	sf::Sprite mCrosshair;
	sf::Sprite mPistol;
	sf::Texture mCrosshairTex;
	sf::Texture mCrosshairReloadTex;
	sf::Texture mPistolTex;
	sf::Text mAmmunition;
	sf::Font mFont;
	unsigned int mMaxAmmo;
	unsigned int mAmmoCount;
};