#include "Player.h"

Player::Player(sf::RenderWindow* window) {
	if (!mTexture.loadFromFile("Resources/PlayerAim1.png")) {

	}
	mSprite.setTexture(mTexture);

    sf::Vector2f playerPos;
    sf::Vector2f playerScale(2.0f, 2.0f);
    playerPos.x = window->getSize().x * .5f;
    playerPos.y = window->getSize().y * .5f;
    sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
    this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
    this->SetPosition(playerPos);
    this->SetScale(playerScale);
}

void Player::Update(sf::RenderWindow* window, float mElapsed) {
    CheckPlayerBounds(window);

    mCursorPos = sf::Vector2f(sf::Mouse::getPosition(*window));
    SetRotation(atan2f(mCursorPos.y - mPosition.y, mCursorPos.x - mPosition.x) * (180 / PI));

}

void Player::MoveObject(sf::Vector2f pos) {
	mSprite.move(pos);
	mPosition = mSprite.getPosition();
}

void Player::SetPosition(sf::Vector2f pos) {
	mSprite.setPosition(pos);
	mPosition = pos;
}

void Player::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

void Player::SetRotation(float angle) {
    mSprite.setRotation(angle);
}

void Player::CheckPlayerBounds(sf::RenderWindow* window) {
    if (mPosition.x < 0) {
        //SetPosition(sf::Vector2f(window->getSize().x, mPosition.y));
        SetPosition(sf::Vector2f(0.f, mPosition.y));
    }
    if (mPosition.x > (int)window->getSize().x) {
        //SetPosition(sf::Vector2f(0.f, mPosition.y));
        SetPosition(sf::Vector2f(window->getSize().x, mPosition.y));
    }
    if (mPosition.y < 0) {
        //SetPosition(sf::Vector2f(mPosition.x, window->getSize().y));
        SetPosition(sf::Vector2f(mPosition.x, 0.f));
    }
    if (mPosition.y > (int)window->getSize().y) {
        //SetPosition(sf::Vector2f(mPosition.x, 0.f));
        SetPosition(sf::Vector2f(mPosition.x, window->getSize().y));
    }
}