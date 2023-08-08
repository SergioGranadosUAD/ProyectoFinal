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

    mCurrentAmmo = MAX_AMMO;

    sf::Vector2f playerPos;
    sf::Vector2f playerScale(1.0f, 1.0f);
    if (!mWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mWindow.lock();
        playerPos.x = windowPtr->getSize().x * .5f;
        playerPos.y = windowPtr->getSize().y * .5f;
    }

    
    
    sf::FloatRect spriteSize = this->GetSprite()->getGlobalBounds();
    this->GetSprite()->setOrigin((spriteSize.width * .5f) - 3.f, spriteSize.height * .5f);
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
}

Player::~Player() {

}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Este método actualiza el jugador cada frame, encargándose de rotar al jugador dependiendo del cursor.
* @details:  Sin comentarios.
*************************************/
void Player::Update() {
    MoveObject(mVelocity);
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
    
    SetRotation(atan2f(mCursorPos.y - mPosition->y, mCursorPos.x - mPosition->x) * (180 / PI));
}

/************************************
* @method:   MoveObject
* @access:   public
* @return    void
* @brief:    Este método mueve el objecto en una dirección específica, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Player::MoveObject(sf::Vector2f pos) {
	mHitbox.move(pos);
    mSprite.move(pos);
	*mPosition = mHitbox.getPosition();
}

/************************************
* @method:   SetPosition
* @access:   public
* @return    void
* @brief:    Este método establece la posición del objeto en un punto exacto, y actualiza el miembro de posición.
* @details:  Sin comentarios.
*************************************/
void Player::SetPosition(sf::Vector2f pos) {
	mHitbox.setPosition(pos);
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
* @method:   SetHitbox
* @access:   public
* @return    void
* @brief:    Este método establece los límites del hitbox de una entidad.
* @details:  Sin comentarios.
*************************************/
void Player::SetHitbox(const sf::RectangleShape& hitbox) {
    mHitbox = hitbox;
}

/************************************
* @method:   AddVelocity
* @access:   public
* @return    void
* @brief:    Este método establece la velocidad que tendrá la entidad en un frame.
* @details:  Sin comentarios.
*************************************/
void Player::AddVelocity(const sf::Vector2f& vel) {
    mVelocity += vel;
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
* @brief:    Este método revisa si el jugador colisiona con un muro, y de ser así, lo detiene.
* @details:  Sin comentarios.
*************************************/
void Player::CheckPlayerBounds(const sf::FloatRect& playerBounds, const sf::FloatRect& wallBounds) {
    if (playerBounds.top < wallBounds.top
        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
        && playerBounds.left < wallBounds.left + wallBounds.width
        && playerBounds.left + playerBounds.width > wallBounds.left) {
        mVelocity.y = 0;
        SetPosition(sf::Vector2f(playerBounds.left+8.f, wallBounds.top - playerBounds.height+8.f));
    } else if (playerBounds.top > wallBounds.top
        && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
        && playerBounds.left < wallBounds.left + wallBounds.width
        && playerBounds.left + playerBounds.width > wallBounds.left) {
        mVelocity.y = 0;
        SetPosition(sf::Vector2f(playerBounds.left+8.f, wallBounds.top + wallBounds.height+8.f));
    } else if (playerBounds.left < wallBounds.left
        && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
        && playerBounds.top < wallBounds.top + wallBounds.height
        && playerBounds.top + playerBounds.height > wallBounds.top) {
        mVelocity.x = 0;
        SetPosition(sf::Vector2f(wallBounds.left - playerBounds.width+8.f, playerBounds.top+8.f));
    }
    else if (playerBounds.left > wallBounds.left
        && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
        && playerBounds.top < wallBounds.top + wallBounds.height
        && playerBounds.top + playerBounds.height > wallBounds.top) {
        mVelocity.x = 0;
        SetPosition(sf::Vector2f(wallBounds.left + wallBounds.width+8.f, playerBounds.top+8.f));
    }
}

/************************************
* @method:   ResetVelocity
* @access:   public
* @return    void
* @brief:    Este método reinicia la velocidad de la entidad para que se vuelva a calcular el siguiente frame.
* @details:  Sin comentarios.
*************************************/
void Player::ResetVelocity() {
    mVelocity.x = 0;
    mVelocity.y = 0;
}

void Player::ShootWeapon() {
    mCurrentAmmo--;
    if (mCurrentAmmo == 0) {
        ReloadWeapon();
    }
}

void Player::ReloadWeapon() {
    std::cout << "Is reloading" << std::endl;
    mReloading = true;
    ResetReloadTimer();
}

void Player::SetAmmunition(const int& ammo) {
    mReloading = false;
    mCurrentAmmo = ammo;
}

void Player::ResetReloadTimer() {
    mReloadTime.restart();
}