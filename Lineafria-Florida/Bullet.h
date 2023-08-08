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
	Bullet(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<float> elapsed, sf::Vector2f pos, float angle, BULLET_ID id);
	virtual ~Bullet();
	void MoveObject(sf::Vector2f pos);
	void SetPosition(sf::Vector2f pos);
	void SetScale(sf::Vector2f scale);
	void SetRotation(float angle);
	void SetHitbox(const sf::RectangleShape& hitbox);

	void Update();

	inline sf::Sprite* GetSprite() { return &mSprite; }
	inline float GetRotation() { return mSprite.getRotation(); }
	inline sf::Vector2f GetPosition() { return mPosition; }
	inline int GetSpeed() { return MAX_SPEED; }
	inline sf::FloatRect GetHitbox() const { return mHitbox.getGlobalBounds(); }
	inline BULLET_ID GetID() { return mID; }

	sf::RectangleShape mHitbox;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	std::weak_ptr<sf::RenderWindow> mWindow;
	std::weak_ptr<float> mElapsed;
	BULLET_ID mID;
	const int MAX_SPEED = 700;
	const double PI = 3.1416;
};
