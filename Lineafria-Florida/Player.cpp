#include "Player.h"

/************************************
* @method:   Player
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Player, carga la textura y asigna los valores iniciales del jugador.
* @details:  Sin comentarios.
*************************************/
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
    this->SetHealth(MAX_HEALTH);
}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Este método actualiza el jugador cada frame, encargándose de rotar al jugador dependiendo del cursor.
* @details:  Sin comentarios.
*************************************/
void Player::Update(sf::RenderWindow* window, const float& mElapsed) {
    CheckPlayerBounds(window);

    mCursorPos = sf::Vector2f(sf::Mouse::getPosition(*window));
    SetRotation(atan2f(mCursorPos.y - mPosition.y, mCursorPos.x - mPosition.x) * (180 / PI));

}

//Unused
void Player::Update(sf::RenderWindow* window, const float& mElapsed, sf::Vector2f playerPos) {

}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este método mueve el objecto en una dirección específica, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Player::MoveObject(sf::Vector2f pos) {
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
void Player::SetPosition(sf::Vector2f pos) {
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
void Player::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este método establece la rotación del objeto.
* @details:  Sin comentarios.
*************************************/
void Player::SetRotation(float angle) {
    mSprite.setRotation(angle);
}

/************************************
* @method:   SetHealth
* @access:   public
* @return    void
* @brief:    Este método establece la cantidad de vida que tendrá una entidad.
* @details:  Sin comentarios.
*************************************/
void Player::SetHealth(int hp) {
    mHealth = hp;
}

/************************************
* @method:   TakeDamage
* @access:   public
* @return    void
* @brief:    Este método recibe un valor de daño y se lo resta a la vida de la entidad.
* @details:  Sin comentarios.
*************************************/
void Player::TakeDamage(int damage) {
    mHealth -= damage;
}

/************************************
* @method:   CheckPlayerBounds
* @access:   public
* @return    void
* @brief:    Este método revisa si el jugador se intenta salir de la ventana, y lo detiene de ser así.
* @details:  Sin comentarios.
*************************************/
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