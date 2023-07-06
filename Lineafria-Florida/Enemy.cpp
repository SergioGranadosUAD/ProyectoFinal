#include "Enemy.h"
#include <iostream>

/************************************
* @method:   Enemy
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Enemy, carga su textura, se la asigna y establece sus valores iniciales.
* @details:  Sin comentarios.
*************************************/
Enemy::Enemy(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<float> elapsed, std::weak_ptr<sf::Vector2f> playerPos, sf::Vector2f pos, ENEMY_TYPE type) {
	if (!mTexture.loadFromFile("Resources/EnemyAim.png")) {

	}
	mSprite.setTexture(mTexture);

	mWindow = window.lock();
	mElapsed = elapsed.lock();
	mPlayerPos = playerPos.lock();

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

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Método que actualiza al enemigo cada frame. Dependiendo del tipo de enemigo que es, ejecuta un comportamiento diferente.
* @details:  Sin comentarios.
*************************************/
void Enemy::Update() {

	switch (mType) {
	case ENEMY_TYPE::CHASER:
		ChasePlayer();
		break;
	case ENEMY_TYPE::SHOOTER:
		ShootPlayer();
		break;
	}
}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este método mueve el objecto en una dirección específica, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Enemy::MoveObject(sf::Vector2f pos) {
	mSprite.move(pos);
	mPosition = mSprite.getPosition();
}

/************************************
* @method:   SetPosition
* @access:   public
* @return    void
* @brief:    Este método establece la posición del objeto en un punto exacto, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetPosition(sf::Vector2f pos) {
	mSprite.setPosition(pos);
	mPosition = pos;
}

/************************************
* @method:   SetScale
* @access:   public
* @return    void
* @brief:    Este método establece la escala del objeto.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este método establece la rotación del objeto.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetRotation(float angle) {
	mSprite.setRotation(angle);
}

/************************************
* @method:   SetHealth
* @access:   public
* @return    void
* @brief:    Este método establece la cantidad de vida que tendrá una entidad.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetHealth(int hp) {
	mHealth = hp;
}

/************************************
* @method:   TakeDamage
* @access:   public
* @return    void
* @brief:    Este método recibe un valor de daño y se lo resta a la vida de la entidad.
* @details:  Sin comentarios.
*************************************/
void Enemy::TakeDamage(int damage) {
	mHealth -= damage;
}

/************************************
* @method:   RestartCooldown
* @access:   public
* @return    void
* @brief:    Este método reinicia el timer de enfriamiento que tiene el enemigo en sus ataques.
* @details:  Sin comentarios.
*************************************/
void Enemy::RestartCooldown() {
	cooldownTimer.restart();
}

/************************************
* @method:   ChasePlayer
* @access:   public
* @return    void
* @brief:    Comportamiento específico de un tipo de enemigo. Persigue al jugador para intentar acercarse a él.
* @details:  Sin comentarios.
*************************************/
void Enemy::ChasePlayer() {
	this->SetRotation(atan2f(mPlayerPos.get()->y - mPosition.y, mPlayerPos.get()->x - mPosition.x) * (180 / PI));
	sf::Vector2f direction;
	direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED * *mElapsed;
	direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED * *mElapsed;
	this->MoveObject(direction);
}

/************************************
* @method:   ShootPlayer
* @access:   public
* @return    void
* @brief:    Comportamiento específico de un tipo de enemigo. Le dispara al jugador desde lejos y trata de mantener su distancia.
* @details:  Sin comentarios.
*************************************/
void Enemy::ShootPlayer() {

}