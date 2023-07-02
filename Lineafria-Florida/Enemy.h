#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy(sf::RenderWindow* window, sf::Vector2f pos);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void TakeDamage(int damage);
	void Update(sf::RenderWindow* window, const float& mElapsed);
	

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }
	inline int GetHealth() { return mHealth; }
	inline sf::FloatRect GetHitbox() { return mHitbox; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mCursorPos;
	sf::FloatRect mHitbox;
	int mHealth;
	const int MAX_HEALTH = 100;
	const int MAX_SPEED = 500;
	const float PI = 3.1416;
};