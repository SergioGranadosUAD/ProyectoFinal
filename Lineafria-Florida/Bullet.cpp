#include "Bullet.h"
#include <iostream>

/************************************
* @method:   Bullet
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Bullet, carga la textura de esta y le asigna los valores iniciales.
* @details:  Sin comentarios.
*************************************/
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

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Este m�todo actualiza el proyectil cada frame, movi�ndolo en la direcci�n en la que se encuentra la rotaci�n.
* @details:  Sin comentarios.
*************************************/
void Bullet::Update(sf::RenderWindow* window, const float& mElapsed) {
	sf::Vector2f direction;
	direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED * mElapsed;
	this->MoveObject(direction);
}

//Unused
void Bullet::Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos) {

}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este m�todo mueve el objecto en una direcci�n espec�fica, y actualiza el miembro de posici�n.
* @details:  Sin comentarios.
*************************************/
void Bullet::MoveObject(sf::Vector2f pos) {
	mSprite.move(pos);
	mPosition = mSprite.getPosition();
}

/************************************
* @method:   SetPosition
* @access:   public
* @return    void
* @brief:    Este m�todo establece la posici�n del objeto en un punto exacto, y actualiza el miembro de posici�n.
* @details:  Sin comentarios.
*************************************/
void Bullet::SetPosition(sf::Vector2f pos) {
	mSprite.setPosition(pos);
	mPosition = pos;
}

/************************************
* @method:   SetScale
* @access:   public
* @return    void
* @brief:    Este m�todo establece la escala del objeto.
* @details:  Sin comentarios.
*************************************/
void Bullet::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este m�todo establece la rotaci�n del objeto.
* @details:  Sin comentarios.
*************************************/
void Bullet::SetRotation(float angle) {
	mSprite.setRotation(angle);
}