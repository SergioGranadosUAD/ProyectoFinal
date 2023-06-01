#pragma once
#include <sfml/Graphics.hpp>
class Entity {
public:
	Entity();
	~Entity();

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;

};