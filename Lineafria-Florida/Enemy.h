#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"

/************************************
* @class:    ENEMY_TYPE
* @access:   public
* @brief:    Este enum sirve para definir el tipo de enemigo, lo cual define su comportamiento.
* @details:  Sin detalles.
*************************************/
enum ENEMY_TYPE {
	CHASER = 0,
	SHOOTER = 1
};

/************************************
* @class:    Enemy
* @access:   public
* @brief:    Esta clase, derivada de Entity, corresponde a los enemigos, y presenta múltiples preset para los enemigos que puede haber.
* @details:  Contiene diferentes comportamientos dependiendo del tipo de enemigo del que se trate.
*************************************/
class Enemy : public Entity {
public:
	Enemy(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<float> elapsed, std::weak_ptr<sf::Vector2f> playerPos, sf::Vector2f pos, ENEMY_TYPE type);
	virtual ~Enemy();
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void SetHitbox(const sf::RectangleShape& hitbox);
	void AddVelocity(const sf::Vector2f& vel);
	void ResetVelocity();
	void TakeDamage(int damage);
	void Update();
	void ChasePlayer();
	void ShootPlayer();
	void RestartCooldown();
	void CheckEnemyBounds(const sf::FloatRect& playerBounds, const sf::FloatRect& objectBounds);
	
	float GetPlayerDistance();
	int GetSpeed();
	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline float GetRotation() { return mSprite.getRotation(); }
	inline int GetHealth() { return mHealth; }
	inline float GetCooldownTime() { return cooldownTimer.getElapsedTime().asMilliseconds(); }
	inline ENEMY_TYPE GetType() const { return mType; }
	inline sf::FloatRect GetHitbox() const { return mHitbox.getGlobalBounds(); }
	inline sf::Vector2f GetVelocity() const { return mVelocity; }
	inline bool HasBeenStartled() const { return mHasBeenStartled; }
	

	sf::RectangleShape mHitbox;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mCursorPos;
	sf::Clock cooldownTimer;
	//sf::RectangleShape mHitbox;
	int mHealth;
	sf::Vector2f mVelocity;
	const int MAX_HEALTH_CHASER = 100;
	const int MAX_SPEED_CHASER = 150;
	const int MAX_HEALTH_SHOOTER = 100;
	const int MAX_SPEED_SHOOTER = 50;
	
	const double PI = 3.1416;
	ENEMY_TYPE mType;

	bool mHasBeenStartled;
	std::weak_ptr<sf::Vector2f> mPlayerPos;
	std::weak_ptr<sf::RenderWindow> mWindow;
	std::weak_ptr<float> mElapsed;
};