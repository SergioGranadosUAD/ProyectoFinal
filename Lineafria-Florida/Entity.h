#pragma once
#include <sfml/Graphics.hpp>
#include <memory>

/************************************
* @class:    Entity
* @access:   public
* @brief:    Esta clase abstracta sirve como base para los tipos de entidades del juego.
* @details:  Cuenta con los aspectos base de cualquier entidad como su textura, sprite y posición, así como un conjunto de métodos para su actualización y
*			 la modificación de sus valores.
*************************************/
class Entity: public sf::Sprite {
public:
	Entity();
	virtual ~Entity();

	virtual void MoveObject(sf::Vector2f pos) = 0;
	virtual void SetPosition(sf::Vector2f pos) = 0;
	virtual void SetScale(sf::Vector2f scale) = 0;
	virtual void SetRotation(float angle) = 0;

	virtual void Update() = 0;
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	std::weak_ptr<sf::Vector2i> mPosition;
};