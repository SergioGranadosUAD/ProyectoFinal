#include "Bullet.h"
#include <iostream>

/************************************
* @method:   Bullet
* @access:   public
* @return    void
* @brief:    Constructor de la clase Bullet, carga la textura de esta y le asigna los valores iniciales.
* @details:  Sin comentarios.
*************************************/
Bullet::Bullet(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<float> elapsed, sf::Vector2f pos, float angle, BULLET_ID id) {
	if (!mTexture.loadFromFile("Resources/Projectiles.png")) {

	}

	mWindow = window;
	mElapsed = elapsed;

	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(256, 128, 16, 16));
	sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
	this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
	this->SetPosition(pos);
	this->SetScale(sf::Vector2f(1.0f, .5f));
	this->SetRotation(angle);
	mID = id;
	std::cout << "Projectile created." << std::endl;

	sf::RectangleShape rect{ sf::Vector2f(3.f, 3.f) };
	rect.setOrigin(spriteSize.height * .5f, spriteSize.height * .5f);
	rect.setPosition(mPosition.x+10.f,mPosition.y+6.5f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Red);
	this->SetHitbox(rect);
}

/************************************
* @method:   ~Bullet
* @access:   public
* @return    void
* @brief:    Destructor de la clase Bullet.
* @details:  Sin comentarios.
*************************************/
Bullet::~Bullet() {
	std::cout << "Projectile destroyed." << std::endl;
}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Este método actualiza el proyectil cada frame, moviéndolo en la dirección en la que se encuentra la rotación.
* @details:  Sin comentarios.
*************************************/
void Bullet::Update() {
	if (!mElapsed.expired()) {
		sf::Vector2f direction;
		std::shared_ptr<float> elapsedPtr = mElapsed.lock();
		direction.x = cos((PI / 180) * mSprite.getRotation()) * MAX_SPEED * *elapsedPtr;
		direction.y = sin((PI / 180) * mSprite.getRotation()) * MAX_SPEED * *elapsedPtr;
		this->MoveObject(direction);
	}
	
}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este método mueve el objecto en una dirección específica, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Bullet::MoveObject(sf::Vector2f pos) {
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
void Bullet::SetPosition(sf::Vector2f pos) {
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
void Bullet::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este método establece la rotación del objeto.
* @details:  Sin comentarios.
*************************************/
void Bullet::SetRotation(float angle) {
	mSprite.setRotation(angle);
}

/************************************
* @method:   SetHitbox
* @access:   public
* @return    void
* @brief:    Este método establece los límites del hitbox de una entidad.
* @details:  Sin comentarios.
*************************************/
void Bullet::SetHitbox(const sf::RectangleShape& hitbox) {
	mHitbox = hitbox;
}