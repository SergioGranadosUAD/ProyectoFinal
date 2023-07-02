#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::RenderWindow* window, sf::Vector2f pos, float angle, BULLET_ID id) {
	if (!mTexture.loadFromFile("Resources/Projectiles.png")) {

	}
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(256, 128, 16, 16));
	sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
	this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
	this->SetPosition(pos);
	this->SetScale(sf::Vector2f(2.0f, 2.0f));
	this->SetRotation(angle);
	mID = id;
	std::cout << "Projectile created." << std::endl;
}

void Bullet::Update(sf::RenderWindow* window, const float& mElapsed) {
	sf::Vector2f direction;
	direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	this->MoveObject(direction);
}

void Bullet::MoveObject(sf::Vector2f pos) {
	mSprite.move(pos);
	mPosition = mSprite.getPosition();
}

void Bullet::SetPosition(sf::Vector2f pos) {
	mSprite.setPosition(pos);
	mPosition = pos;
}

void Bullet::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

void Bullet::SetRotation(float angle) {
	mSprite.setRotation(angle);
}