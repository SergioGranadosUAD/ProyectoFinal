#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"

class Player : public Entity {
public:
	Player(sf::RenderWindow* window);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void CheckPlayerBounds(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float mElapsed);

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mCursorPos;
	const int MAX_SPEED = 500;
	const float PI = 3.1416;
};
