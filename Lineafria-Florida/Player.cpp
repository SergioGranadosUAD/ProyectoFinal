#include "Player.h"

/************************************
* @method:   Player
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Player, carga la textura y asigna los valores iniciales del jugador.
* @details:  Sin comentarios.
*************************************/
Player::Player(std::weak_ptr<sf::RenderWindow> window) {
	if (!mTexture.loadFromFile("Resources/PlayerAim1.png")) {

	}
	mSprite.setTexture(mTexture);

    mWindow = window.lock();
    mPosition = std::make_shared<sf::Vector2f>(0.f, 0.f);

    sf::Vector2f playerPos;
    sf::Vector2f playerScale(2.0f, 2.0f);
    playerPos.x = mWindow.get()->getSize().x * .5f;
    playerPos.y = mWindow.get()->getSize().y * .5f;
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
void Player::Update() {
    CheckPlayerBounds();

    mCursorPos = sf::Vector2f(sf::Mouse::getPosition(*mWindow.get()));
    SetRotation(atan2f(mCursorPos.y - mPosition.get()->y, mCursorPos.x - mPosition.get()->x) * (180 / PI));

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
	*mPosition = mSprite.getPosition();
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
	*mPosition = pos;
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
void Player::CheckPlayerBounds() {
    if (mPosition.get()->x < 0) {
        //SetPosition(sf::Vector2f(window->getSize().x, mPosition.y));
        SetPosition(sf::Vector2f(0.f, mPosition.get()->y));
    }
    if (mPosition.get()->x > (int)mWindow.get()->getSize().x) {
        //SetPosition(sf::Vector2f(0.f, mPosition.y));
        SetPosition(sf::Vector2f(mWindow.get()->getSize().x, mPosition.get()->y));
    }
    if (mPosition.get()->y < 0) {
        //SetPosition(sf::Vector2f(mPosition.x, window->getSize().y));
        SetPosition(sf::Vector2f(mPosition.get()->x, 0.f));
    }
    if (mPosition.get()->y >(int)mWindow.get()->getSize().y) {
        //SetPosition(sf::Vector2f(mPosition.x, 0.f));
        SetPosition(sf::Vector2f(mPosition.get()->x, mWindow.get()->getSize().y));
    }
}