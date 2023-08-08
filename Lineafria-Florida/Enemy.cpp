#include "Enemy.h"

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
	mHasBeenStartled = false;

	sf::Vector2f enemyScale(1.0f, 1.0f);
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

	sf::RectangleShape rect{ sf::Vector2f(spriteSize.height, spriteSize.height) };
	rect.setOrigin(spriteSize.height * .5f, spriteSize.height * .5f);
	rect.setPosition(pos);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Red);
	this->SetHitbox(rect);
}

Enemy::~Enemy() {

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
	mHitbox.move(pos);
	mSprite.move(pos);
	mPosition = mHitbox.getPosition();
}

/************************************
* @method:   SetPosition
* @access:   public
* @return    void
* @brief:    Este método establece la posición del objeto en un punto exacto, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetPosition(sf::Vector2f pos) {
	mHitbox.setPosition(pos);
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
* @method:   SetHitbox
* @access:   public
* @return    void
* @brief:    Este método establece los límites del hitbox de una entidad.
* @details:  Sin comentarios.
*************************************/
void Enemy::SetHitbox(const sf::RectangleShape& hitbox) {
	mHitbox = hitbox;
}

/************************************
* @method:   GetSpeed
* @access:   public
* @return    int
* @brief:    Este método regresa la velocidad del enemigo dependiendo su tipo.
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
* @method:   AddVelocity
* @access:   public
* @return    void
* @brief:    Este método establece la velocidad que tendrá la entidad en un frame.
* @details:  Sin comentarios.
*************************************/
void Enemy::AddVelocity(const sf::Vector2f& vel) {
	mVelocity += vel;
}

/************************************
* @method:   ResetVelocity
* @access:   public
* @return    void
* @brief:    Este método reinicia la velocidad de la entidad para que se vuelva a calcular el siguiente frame.
* @details:  Sin comentarios.
*************************************/
void Enemy::ResetVelocity() {
	mVelocity.x = 0;
	mVelocity.y = 0;
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
	if (!mPlayerPos.expired() && !mElapsed.expired()) {
		std::shared_ptr<sf::Vector2f> playerPosPtr = mPlayerPos.lock();
		std::shared_ptr<float> elapsedPtr = mElapsed.lock();
		if (GetPlayerDistance() < 150) {
			mHasBeenStartled = true;
		}
		
		if (mHasBeenStartled) {
			this->SetRotation(atan2f(playerPosPtr->y - mPosition.y, playerPosPtr->x - mPosition.x) * (180 / PI));
			sf::Vector2f direction;
			direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED_CHASER * *elapsedPtr;
			direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED_CHASER * *elapsedPtr;
			this->AddVelocity(direction);
		}
	}
	
}

/************************************
* @method:   ShootPlayer
* @access:   public
* @return    void
* @brief:    Comportamiento específico de un tipo de enemigo. Le dispara al jugador desde lejos y trata de mantener su distancia.
* @details:  Sin comentarios.
*************************************/
void Enemy::ShootPlayer() {
	if (!mPlayerPos.expired() && !mElapsed.expired()) {
		std::shared_ptr<sf::Vector2f> playerPosPtr = mPlayerPos.lock();
		std::shared_ptr<float> elapsedPtr = mElapsed.lock();
		if (GetPlayerDistance() < 300) {
			mHasBeenStartled = true;
		}

		if (mHasBeenStartled) {
			this->SetRotation(atan2f(playerPosPtr->y - mPosition.y, playerPosPtr->x - mPosition.x) * (180 / PI));
			if (GetPlayerDistance() < 100) {
				sf::Vector2f direction;
				direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED_SHOOTER * *elapsedPtr;
				direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED_SHOOTER * *elapsedPtr;
				this->AddVelocity(-direction);
			}
			
		}
	}
}

float Enemy::GetPlayerDistance() {
	if (!mPlayerPos.expired()) {
		std::shared_ptr<sf::Vector2f> playerPosPtr = mPlayerPos.lock();
		return sqrt(pow(mPosition.x - playerPosPtr->x, 2) + pow(mPosition.y - playerPosPtr->y, 2));
	}
	
}

void Enemy::CheckEnemyBounds(const sf::FloatRect& playerBounds, const sf::FloatRect& wallBounds) {
	if (playerBounds.top < wallBounds.top
		&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
		&& playerBounds.left < wallBounds.left + wallBounds.width
		&& playerBounds.left + playerBounds.width > wallBounds.left) {
		mVelocity.y = 0;
		SetPosition(sf::Vector2f(playerBounds.left + 9.f, wallBounds.top - playerBounds.height + 9.f));
	}
	else if (playerBounds.top > wallBounds.top
		&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
		&& playerBounds.left < wallBounds.left + wallBounds.width
		&& playerBounds.left + playerBounds.width > wallBounds.left) {
		mVelocity.y = 0;
		SetPosition(sf::Vector2f(playerBounds.left + 9.f, wallBounds.top + wallBounds.height + 9.f));
	}
	else if (playerBounds.left < wallBounds.left
		&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
		&& playerBounds.top < wallBounds.top + wallBounds.height
		&& playerBounds.top + playerBounds.height > wallBounds.top) {
		mVelocity.x = 0;
		SetPosition(sf::Vector2f(wallBounds.left - playerBounds.width + 9.f, playerBounds.top + 9.f));
	}
	else if (playerBounds.left > wallBounds.left
		&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
		&& playerBounds.top < wallBounds.top + wallBounds.height
		&& playerBounds.top + playerBounds.height > wallBounds.top) {
		mVelocity.x = 0;
		SetPosition(sf::Vector2f(wallBounds.left + wallBounds.width + 9.f, playerBounds.top + 9.f));
	}
}