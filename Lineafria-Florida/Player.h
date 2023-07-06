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
	Player(std::weak_ptr<sf::RenderWindow> window);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHealth(int hp);
	void TakeDamage(int damage);
	void CheckPlayerBounds();

	void Update();

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline std::weak_ptr<sf::Vector2f> GetPosition() { return mPosition; }
	inline int GetHealth() { return mHealth; }
	inline int GetSpeed() { return MAX_SPEED; }

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	std::shared_ptr<sf::Vector2f> mPosition;
	std::shared_ptr<sf::RenderWindow> mWindow;
	sf::Vector2f mCursorPos;
	int mHealth;
	const int MAX_HEALTH = 100;
	const int MAX_SPEED = 300;
	const float PI = 3.1416;
};
