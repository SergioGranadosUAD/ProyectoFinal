#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"

enum ENEMY_TYPE {
	CHASER = 0,
	SHOOTER = 1
};

class Enemy : public Entity {
public:
	Enemy(sf::RenderWindow* window, sf::Vector2f pos, ENEMY_TYPE type);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void TakeDamage(int damage);
	void Update(sf::RenderWindow* window, const float& mElapsed);
	void Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos);
	void ChasePlayer(float mElapsed, sf::Vector2f playerPos);
	void ShootPlayer(float mElapsed, sf::Vector2f playerPos);
	void RestartCooldown();
	

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }
	inline int GetHealth() { return mHealth; }
	inline float GetCooldownTime() { return cooldownTimer.getElapsedTime().asMilliseconds(); }
	/*inline sf::FloatRect GetHitbox() { return mHitbox; }*/

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mCursorPos;
	sf::Clock cooldownTimer;
	//sf::FloatRect mHitbox;
	int mHealth;
	int MAX_HEALTH = 100;
	int MAX_SPEED = 500;
	const float PI = 3.1416;
	ENEMY_TYPE mType;
};