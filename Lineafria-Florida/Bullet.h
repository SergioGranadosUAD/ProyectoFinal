#pragma once
#include <sfml/Graphics.hpp>
#include <cmath>
#include "Entity.h"

class Bullet : public Entity {
public:
	Bullet(sf::RenderWindow* window, sf::Vector2f pos, float angle);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void Update(sf::RenderWindow* window, float mElapsed);

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	const int MAX_SPEED = 1000;
	const float PI = 3.1416;
};
