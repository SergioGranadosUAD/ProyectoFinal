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

	mWindow = window;
	mElapsed = elapsed;
	mPlayerPos = playerPos;

	sf::Vector2f enemyScale(2.0f, 2.0f);
	sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
	this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
	this->SetPosition(pos);
	this->SetScale(enemyScale);

	mType = type;

	if (mType == ENEMY_TYPE::CHASER) {
		this->SetHealth(MAX_HEALTH_CHASER);
	}
	else if (mType == ENEMY_TYPE::SHOOTER) {
		this->SetHealth(MAX_HEALTH_SHOOTER);
	}

	

	//Hitbox arbitraria, falta definir.
	//mHitbox = sf::FloatRect(pos.x-11, pos.y-8, 15.f, 14.f);
}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    M�todo que actualiza al enemigo cada frame. Dependiendo del tipo de enemigo que es, ejecuta un comportamiento diferente.
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
* @brief:    Este m�todo mueve el objecto en una direcci�n espec�fica, y actualiza el miembro de posici�n.
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
* @brief:    Este m�todo establece la posici�n del objeto en un punto exacto, y actualiza el miembro de posici�n.
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
* @brief:    Este m�todo establece la escala del objeto.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este m�todo establece la rotaci�n del objeto.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetRotation(float angle) {
	mSprite.setRotation(angle);
}

/************************************
* @method:   SetHealth
* @access:   public
* @return    void
* @brief:    Este m�todo establece la cantidad de vida que tendr� una entidad.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetHealth(int hp) {
	mHealth = hp;
}

/************************************
* @method:   GetSpeed
* @access:   public
* @return    int
* @brief:    Este m�todo regresa la velocidad del enemigo dependiendo su tipo.
* @details:  Sin comentarios.
*************************************/
int Enemy::GetSpeed() {
	if (mType == ENEMY_TYPE::CHASER) {
		return MAX_SPEED_CHASER;
	}
	else if (mType == ENEMY_TYPE::SHOOTER) {
		return MAX_SPEED_SHOOTER;
	}
}

/************************************
* @method:   TakeDamage
* @access:   public
* @return    void
* @brief:    Este m�todo recibe un valor de da�o y se lo resta a la vida de la entidad.
* @details:  Sin comentarios.
*************************************/
void Enemy::TakeDamage(int damage) {
	mHealth -= damage;
}

/************************************
* @method:   RestartCooldown
* @access:   public
* @return    void
* @brief:    Este m�todo reinicia el timer de enfriamiento que tiene el enemigo en sus ataques.
* @details:  Sin comentarios.
*************************************/
void Enemy::RestartCooldown() {
	cooldownTimer.restart();
}

/************************************
* @method:   ChasePlayer
* @access:   public
* @return    void
* @brief:    Comportamiento espec�fico de un tipo de enemigo. Persigue al jugador para intentar acercarse a �l.
* @details:  Sin comentarios.
*************************************/
void Enemy::ChasePlayer() {
	if (!mPlayerPos.expired() && !mElapsed.expired()) {
		std::shared_ptr<sf::Vector2f> playerPosPtr = mPlayerPos.lock();
		std::shared_ptr<float> elapsedPtr = mElapsed.lock();

		this->SetRotation(atan2f(playerPosPtr->y - mPosition.y, playerPosPtr->x - mPosition.x) * (180 / PI));
		sf::Vector2f direction;
		direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED_CHASER * *elapsedPtr;
		direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED_CHASER * *elapsedPtr;
		this->MoveObject(direction);
	}
	
}

/************************************
* @method:   ShootPlayer
* @access:   public
* @return    void
* @brief:    Comportamiento espec�fico de un tipo de enemigo. Le dispara al jugador desde lejos y trata de mantener su distancia.
* @details:  Sin comentarios.
*************************************/
void Enemy::ShootPlayer() {

}