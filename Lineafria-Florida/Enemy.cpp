#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* window, sf::Vector2f pos) {
	if (!mTexture.loadFromFile("Resources/EnemyAim.png")) {

	}
	mSprite.setTexture(mTexture);

	sf::Vector2f enemyScale(2.0f, 2.0f);
	sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
	this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
	this->SetPosition(pos);
	this->SetScale(enemyScale);
	this->SetHealth(MAX_HEALTH);
	//Hitbox arbitraria, falta definir.
	mHitbox = sf::FloatRect(pos.x-11, pos.y-8, 15.f, 14.f);
}

void Enemy::Update(sf::RenderWindow* window, const float& mElapsed) {

}

void Enemy::MoveObject(sf::Vector2f pos) {
	mSprite.move(pos);
	mPosition = mSprite.getPosition();
}

void Enemy::SetPosition(sf::Vector2f pos) {
	mSprite.setPosition(pos);
	mPosition = pos;
}

void Enemy::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

void Enemy::SetRotation(float angle) {
	mSprite.setRotation(angle);
}

void Enemy::SetHealth(int hp) {
	mHealth = hp;
}

void Enemy::TakeDamage(int damage) {
	mHealth -= damage;
}