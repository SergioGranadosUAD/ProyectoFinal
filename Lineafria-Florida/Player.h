#pragma once
#include <sfml/Graphics.hpp>
#include <iostream>
#include "Entity.h"

/************************************
* @class:    Player
* @access:   public
* @brief:    Esta clase, derivada de Entity, corresponde al jugador.
* @details:  Además de heredar métodos de Entity, tiene métodos adicionales útiles para el jugador.
*************************************/
class Player : public Entity {
public:
	Player(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<sf::View> view);
	virtual ~Player();
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void TakeDamage(int damage);
	void SetHitbox(const sf::RectangleShape& hitbox);
	void CheckPlayerBounds(const sf::FloatRect& playerBounds, const sf::FloatRect& objectBounds);
	void AddVelocity(const sf::Vector2f& vel);
	void ResetVelocity();
	void ShootWeapon();
	void ReloadWeapon();
	void SetAmmunition(const int& ammo);
	void ResetReloadTimer();

	void Update();

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline std::weak_ptr<sf::Vector2f> GetPosition() { return mPosition; }
	inline int GetHealth() { return mHealth; }
	inline int GetSpeed() { return MAX_SPEED; }
	inline sf::FloatRect GetHitbox() const { return mHitbox.getGlobalBounds(); }
	inline sf::Vector2f GetVelocity() const { return mVelocity; }
	inline unsigned int GetMaxAmmo() const { return MAX_AMMO; }
	inline int GetCurrentAmmo() const { return mCurrentAmmo; }
	inline float GetReloadCooldown() const { return mReloadTime.getElapsedTime().asMilliseconds(); }
	inline int GetReloadTime() const { return RELOAD_TIME; }
	inline bool IsReloading() const { return mReloading; }

	sf::RectangleShape mHitbox;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	//sf::RectangleShape mHitbox;
	std::shared_ptr<sf::Vector2f> mPosition;
	std::weak_ptr<sf::RenderWindow> mWindow;
	std::weak_ptr<sf::View> mView;
	sf::Vector2f mCursorPos;
	sf::Vector2f mVelocity;
	int mHealth;
	int mCurrentAmmo;
	sf::Clock mReloadTime;
	bool mReloading;
	const unsigned int MAX_AMMO = 7;
	const int MAX_HEALTH = 100;
	const int MAX_SPEED = 200;
	const int RELOAD_TIME = 2000;
	const double PI = 3.1416;

	
};
