#pragma once
#include <sfml/Graphics.hpp>
#include <cmath>
#include "Entity.h"

/************************************
* @class:    BULLET_ID
* @access:   public
* @brief:    Este enumerador sirve para identificar si se trata de un proyectil aliado o enemigo, lo cual define su comportamiento.
* @details:  Sin detalles.
*************************************/
enum BULLET_ID {
	ALLIED = 0,
	ENEMY = 1,
};

/************************************
* @class:    Bullet
* @access:   public
* @brief:    Esta clase, derivada de Entity, corresponde a los proyectiles disparados por los enemigos y por el jugador.
* @details:  Esta clase casi no tiene variaciones sobre su clase padre.
*************************************/
class Bullet : public Entity {
public:
	Bullet(sf::RenderWindow* window, sf::Vector2f pos, float angle, BULLET_ID id);
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);

	void Update(sf::RenderWindow* window, const float& mElapsed);
	void Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos);

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }
	inline BULLET_ID GetID() { return mID; }
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	BULLET_ID mID;
	const int MAX_SPEED = 1000;
	const float PI = 3.1416;
};
