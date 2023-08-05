#include "Player.h"

/************************************
* @method:   Player
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Player, carga la textura y asigna los valores iniciales del jugador.
* @details:  Sin comentarios.
*************************************/
Player::Player(std::weak_ptr<sf::RenderWindow> window, std::weak_ptr<sf::View> view) {
	if (!mTexture.loadFromFile("Resources/PlayerAim1.png")) {

	}
	mSprite.setTexture(mTexture);

    mWindow = window;
    mView = view;
    mPosition = std::make_shared<sf::Vector2f>(0.f, 0.f);

    sf::Vector2f playerPos;
    sf::Vector2f playerScale(1.0f, 1.0f);
    if (!mWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mWindow.lock();
        playerPos.x = windowPtr->getSize().x * .5f;
        playerPos.y = windowPtr->getSize().y * .5f;
    }

    
    
    sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
    this->GetSprite()->setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);
    this->SetPosition(playerPos);
    this->SetScale(playerScale);
    this->SetHealth(MAX_HEALTH);

    sf::RectangleShape rect{ sf::Vector2f(spriteSize.height, spriteSize.height) };
    rect.setOrigin(spriteSize.height*.5f, spriteSize.height*.5f);
    rect.setPosition(playerPos);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1.f);
    rect.setOutlineColor(sf::Color::Red);
    this->SetHitbox(rect);
    //this->SetHitbox({ -spriteSize.width * .5f, -spriteSize.height * .5f, 14.f, spriteSize.height });

}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Este m�todo actualiza el jugador cada frame, encarg�ndose de rotar al jugador dependiendo del cursor.
* @details:  Sin comentarios.
*************************************/
void Player::Update() {
    if (!mWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mWindow.lock();
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*windowPtr);
        mCursorPos = windowPtr->mapPixelToCoords(pixelPos);

        if (!mView.expired()) {
            std::shared_ptr<sf::View> viewPtr = mView.lock();
            viewPtr->setCenter(*mPosition);
            windowPtr->setView(*viewPtr);
        }

        
    }

    mHitbox.setPosition(*mPosition);
    
    SetRotation(atan2f(mCursorPos.y - mPosition->y, mCursorPos.x - mPosition->x) * (180 / PI));
}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este m�todo mueve el objecto en una direcci�n espec�fica, y actualiza el miembro de posici�n.
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
* @brief:    Este m�todo establece la posici�n del objeto en un punto exacto, y actualiza el miembro de posici�n.
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
* @brief:    Este m�todo establece la escala del objeto.
* @details:  Sin comentarios.
*************************************/
void Player::SetScale(sf::Vector2f scale) {
	mSprite.setScale(scale);
}

/************************************
* @method:   SetRotation
* @access:   public
* @return    void
* @brief:    Este m�todo establece la rotaci�n del objeto.
* @details:  Sin comentarios.
*************************************/
void Player::SetRotation(float angle) {
    mSprite.setRotation(angle);
}

/************************************
* @method:   SetHealth
* @access:   public
* @return    void
* @brief:    Este m�todo establece la cantidad de vida que tendr� una entidad.
* @details:  Sin comentarios.
*************************************/
void Player::SetHealth(int hp) {
    mHealth = hp;
}

/************************************
* @method:   SetHitbox
* @access:   public
* @return    void
* @brief:    Este m�todo establece los l�mites del hitbox de una entidad.
* @details:  Sin comentarios.
*************************************/
void Player::SetHitbox(const sf::RectangleShape& hitbox) {
    mHitbox = hitbox;
}

/************************************
* @method:   AddVelocity
* @access:   public
* @return    void
* @brief:    Este m�todo establece la velocidad que tendr� la entidad en un frame.
* @details:  Sin comentarios.
*************************************/
void Player::AddVelocity(const sf::Vector2f& vel) {
    mVelocity += vel;
}

/************************************
* @method:   TakeDamage
* @access:   public
* @return    void
* @brief:    Este m�todo recibe un valor de da�o y se lo resta a la vida de la entidad.
* @details:  Sin comentarios.
*************************************/
void Player::TakeDamage(int damage) {
    mHealth -= damage;
}

/************************************
* @method:   CheckPlayerBounds
* @access:   public
* @return    void
* @brief:    Este m�todo revisa si el jugador colisiona con un muro, y de ser as�, lo detiene.
* @details:  Sin comentarios.
*************************************/
void Player::CheckPlayerBounds(const sf::FloatRect& objectBounds) {
    sf::FloatRect playerBounds = mHitbox.getGlobalBounds();
    if (playerBounds.top < objectBounds.top
        && playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height
        && playerBounds.left < objectBounds.left + objectBounds.width
        && playerBounds.left + playerBounds.width > objectBounds.left) {
        mVelocity.y = 0;
        this->SetPosition(sf::Vector2f(playerBounds.left, objectBounds.top - playerBounds.height));
    } else if (playerBounds.top > objectBounds.top
        && playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height
        && playerBounds.left < objectBounds.left + objectBounds.width
        && playerBounds.left + playerBounds.width > objectBounds.left) {
        mVelocity.y = 0;
        this->SetPosition(sf::Vector2f(playerBounds.left, objectBounds.top + objectBounds.height));
    } else if (playerBounds.left < objectBounds.left
        && playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width
        && playerBounds.top < objectBounds.top + objectBounds.height
        && playerBounds.top + playerBounds.height > objectBounds.top) {
        mVelocity.x = 0;
        this->SetPosition(sf::Vector2f(objectBounds.left - playerBounds.width, playerBounds.top));
    }
    else if (playerBounds.left > objectBounds.left
        && playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width
        && playerBounds.top < objectBounds.top + objectBounds.height
        && playerBounds.top + playerBounds.height > objectBounds.top) {
        mVelocity.x = 0;
        this->SetPosition(sf::Vector2f(objectBounds.left + objectBounds.width, playerBounds.top));
    }
}

/************************************
* @method:   ResetVelocity
* @access:   public
* @return    void
* @brief:    Este m�todo reinicia la velocidad de la entidad para que se vuelva a calcular el siguiente frame.
* @details:  Sin comentarios.
*************************************/
void Player::ResetVelocity() {
    mVelocity.x = 0;
    mVelocity.y = 0;
}