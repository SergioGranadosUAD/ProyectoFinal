#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"

/************************************
* @class:    Player
* @access:   public
* @brief:    Esta clase, derivada de Entity, corresponde al jugador.
* @details:  Además de heredar métodos de Entity, tiene métodos adicionales útiles para el jugador.
*************************************/
class Player : public Entity {
public:
	Player(sf::RenderWindow* window);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void TakeDamage(int damage);
	void CheckPlayerBounds(sf::RenderWindow* window);

	void Update(sf::RenderWindow* window, const float& mElapsed);
	void Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos);

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetHealth() { return mHealth; }
	inline int GetSpeed() { return MAX_SPEED; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mCursorPos;
	int mHealth;
	const int MAX_HEALTH = 100;
	const int MAX_SPEED = 300;
	const float PI = 3.1416;
};
