#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::RenderWindow* window, sf::Vector2f pos, ENEMY_TYPE type) {
	if (!mTexture.loadFromFile("Resources/EnemyAim.png")) {

	}
	mSprite.setTexture(mTexture);

	sf::Vector2f enemyScale(2.0f, 2.0f);
	sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
	this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
	this->SetPosition(pos);
	this->SetScale(enemyScale);
	
	mType = type;

	if (mType == ENEMY_TYPE::CHASER) {
		MAX_HEALTH = 100;
		MAX_SPEED = 200;
	}
	else if (mType == ENEMY_TYPE::SHOOTER) {
		MAX_HEALTH = 60;
		MAX_SPEED = 100;
	}

	this->SetHealth(MAX_HEALTH);

	//Hitbox arbitraria, falta definir.
	//mHitbox = sf::FloatRect(pos.x-11, pos.y-8, 15.f, 14.f);
}

//Unused
void Enemy::Update(sf::RenderWindow* window, const float& mElapsed) {
}

void Enemy::Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos) {

	switch (mType) {
	case ENEMY_TYPE::CHASER:
		ChasePlayer(mElapsed, playerPos);
		break;
	case ENEMY_TYPE::SHOOTER:
		ShootPlayer(mElapsed, playerPos);
		break;
	}
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

void Enemy::RestartCooldown() {
	cooldownTimer.restart();
}

void Enemy::ChasePlayer(float mElapsed, sf::Vector2f playerPos) {
	this->SetRotation(atan2f(playerPos.y - mPosition.y, playerPos.x - mPosition.x) * (180 / PI));
	sf::Vector2f direction;
	direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	this->MoveObject(direction);
}

void Enemy::ShootPlayer(float mElapsed, sf::Vector2f playerPos) {

}