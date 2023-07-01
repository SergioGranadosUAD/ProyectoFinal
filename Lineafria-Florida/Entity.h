#pragma once
#include <sfml/Graphics.hpp>
class Entity {
public:
	Entity();
	~Entity();

	virtual void MoveObject(sf::Vector2f pos) = 0;
	virtual void SetPosition(sf::Vector2f pos) = 0;
	virtual void SetScale(sf::Vector2f scale) = 0;
	virtual void SetRotation(float angle) = 0;
	virtual void Update(sf::RenderWindow* window, float mElapsed) = 0;

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
};