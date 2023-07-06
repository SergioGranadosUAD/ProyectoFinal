#include "Game.h"

/************************************
* @method:   Game
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Game, establece los valores que llevar� el juego y crea los elementos necesarios para su funcionamiento.
* @details:  Sin detalles.
*************************************/
Game::Game() :
	mWindow(std::make_shared<Window>("Game Window", sf::Vector2u(800, 600))), mElapsed(std::make_shared<float>(0)) {

    mRenderWindow = mWindow->GetMWindow();
    mPlayer = std::make_unique<Player>(mRenderWindow);

    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        windowPtr->setVerticalSyncEnabled(true);
        windowPtr->setKeyRepeatEnabled(false);
    }


    std::shared_ptr<Enemy> enemyPtr(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(100, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr);

    std::shared_ptr<Enemy> enemyPtr2(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(400, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr2);

    std::shared_ptr<Enemy> enemyPtr3(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(700, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr3);
};

Game::~Game(){}

/************************************
* @method:   HandleInput
* @access:   public
* @return    void
* @brief:    Este m�todo se encarga de procesar la entrada por parte del usuario.
* @details:  Presenta varios casos para diversas teclas oprimidas por el usuario.
*************************************/
void Game::HandleInput(){
	sf::Event event;
    //Procesa las diferentes teclas introducidas por el jugador.
    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        while (windowPtr->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.get()->FinishWindow();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                mWindow.get()->ToggleFullscreen();
            }

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed." << std::endl;
                switch (event.key.code) {
                case sf::Keyboard::W:
                    animFlags.upPressed = true;
                    break;
                case sf::Keyboard::S:
                    animFlags.downPressed = true;
                    break;
                case sf::Keyboard::A:
                    animFlags.leftPressed = true;
                    break;
                case sf::Keyboard::D:
                    animFlags.rightPressed = true;
                    break;
                    std::cout << "Mouse pressed" << std::endl;
                    break;

                default:
                    break;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                std::cout << "Key released." << std::endl;
                switch (event.key.code) {
                case sf::Keyboard::W:
                    animFlags.upPressed = false;
                    break;
                case sf::Keyboard::S:
                    animFlags.downPressed = false;
                    break;
                case sf::Keyboard::A:
                    animFlags.leftPressed = false;
                    break;
                case sf::Keyboard::D:
                    animFlags.rightPressed = false;
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::shared_ptr<Bullet> bullet(new Bullet(mRenderWindow, mElapsed, *mPlayer.get()->GetPosition().lock(), mPlayer.get()->GetSprite()->getRotation(), BULLET_ID(ALLIED)));
                    projectiles.push_back(bullet);
                }
            }
        }

        //Mueve al jugador dependiendo de las banderas que se encuentren encedidas.
        if (animFlags.upPressed) {
            mPlayer.get()->MoveObject(sf::Vector2f(0.f, -mPlayer.get()->GetSpeed() * *mElapsed));
        }
        if (animFlags.downPressed) {
            mPlayer.get()->MoveObject(sf::Vector2f(0.f, mPlayer.get()->GetSpeed() * *mElapsed));
        }
        if (animFlags.leftPressed) {
            mPlayer.get()->MoveObject(sf::Vector2f(-mPlayer.get()->GetSpeed() * *mElapsed, 0.f));
        }
        if (animFlags.rightPressed) {
            mPlayer.get()->MoveObject(sf::Vector2f(mPlayer.get()->GetSpeed() * *mElapsed, 0.f));
        }
    }
	
}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    M�todo que actualiza el juego de forma constante, as� como todos los elementos que requieran actualizarse.
* @details:  Sin detalles.
*************************************/
void Game::Update() {

    //Actualizaci�n de todas las entidades en el juego.
    mPlayer.get()->Update();
    for (auto bullet : projectiles) {
        bullet->Update();
    }
    for (auto enemy : enemies) {
        enemy->Update();

        //Ataque cuerpo a cuerpo hacia el jugador.
        if (enemy->GetSprite()->getGlobalBounds().intersects(mPlayer.get()->GetSprite()->getGlobalBounds()) && enemy->GetCooldownTime() > 2000) {
            std::cout << "Melee attack on player." << std::endl;
            mPlayer.get()->TakeDamage(20);
            enemy->RestartCooldown();
        }
    }

    CheckProjectileCollision();

    //Se verifica si el jugador sigue vivo, de lo contrario reinicia el juego.
    if (mPlayer.get()->GetHealth() <= 0) {
        std::cout << "Player death." << std::endl;
        RestartGame();
    }

	RestartClock();
}

/************************************
* @method:   Render
* @access:   public
* @return    void
* @brief:    Este m�todo dibuja todas las entidades en la ventana.
* @details:  Sin detalles.
*************************************/
void Game::Render() {
	mWindow.get()->BeginDraw();
	mWindow.get()->Draw(*mPlayer.get()->GetSprite());
    for (auto bullet : projectiles) {
        mWindow.get()->Draw(*bullet.get()->GetSprite());
    }
    for (auto enemy : enemies) {
        mWindow.get()->Draw(*enemy.get()->GetSprite());
    }
	mWindow.get()->EndDraw();
}

/************************************
* @method:   RestartClock
* @access:   public
* @return    void
* @brief:    Este m�todo reinicia el reloj y le asigna el tiempo que ha pasado desde el �ltimo reinicio a la variable mElapsed.
* @details:  Sin detalles.
*************************************/
void Game::RestartClock() {
	*mElapsed = mClock.restart().asSeconds();
}

/************************************
* @method:   GetElapsed
* @access:   public
* @return    weak_ptr<float>
* @brief:    Este m�todo devuelve el tiempo transcurrido desde el �ltimo reinicio del reloj.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<float> Game::GetElapsed() {
	return mElapsed;
}

/************************************
* @method:   GetWindow
* @access:   public
* @return    weak_ptr<Window>
* @brief:    Este m�todo devuelve un puntero a la ventana para que pueda ser ocupada.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<Window> Game::GetWindow() {
    std::weak_ptr<Window> windowPtr = mWindow;
	return windowPtr;
}

/************************************
* @method:   RestartGame
* @access:   public
* @return    void
* @brief:    Este m�todo reinicia el nivel a su estado inicial, para que se pueda volver a jugar.
* @details:  Sin detalles.
*************************************/
void Game::RestartGame() {
    mPlayer.reset();
    mPlayer = std::make_unique<Player>(mRenderWindow);
    mClock.restart();
    *mElapsed = 0.f;
    animFlags = {};
    projectiles.clear();
    enemies.clear();

    std::shared_ptr<Enemy> enemyPtr(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(100, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr);

    std::shared_ptr<Enemy> enemyPtr2(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(400, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr2);

    std::shared_ptr<Enemy> enemyPtr3(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(700, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr3);
}

/************************************
* @method:   CheckProjectileCollision
* @access:   public
* @return    void
* @brief:    Este m�todo revisa si los proyectiles colisionan con jugador o un enemigo, y realiza los comportamientos apropiados.
* @details:  Sin detalles.
*************************************/
void Game::CheckProjectileCollision() {
    sf::View view;

    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        view = windowPtr->getView();
    }
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    //Iteraci�n de proyectiles.
    for (int i = 0; i < projectiles.size(); ++i) {

        //Se eliminan aquellos proyectiles que salen de la pantalla.
        if (!(viewRect.contains(projectiles[i]->GetPosition()))) {
            projectiles.erase(projectiles.begin() + i);
            //std::cout << "Projectile deleted" << std::endl;
        }
        else {
            //Se comprueba si un proyectil es enemigo y colisiona con el jugador.
            if (projectiles[i].get()->GetSprite()->getGlobalBounds().intersects(mPlayer.get()->GetSprite()->getGlobalBounds()) && projectiles[i].get()->GetID() == BULLET_ID::ENEMY) {
                projectiles.erase(projectiles.begin() + i);
                mPlayer.get()->TakeDamage(20);
                break;
            }

            //Se comprueba si el proyectil es del jugador y colisiona con un enemigo.
            for (int k = 0; k < enemies.size(); ++k) {
                if (projectiles[i].get()->GetSprite()->getGlobalBounds().intersects(enemies[k].get()->GetSprite()->getGlobalBounds()) && projectiles[i].get()->GetID() == BULLET_ID::ALLIED) {
                    projectiles.erase(projectiles.begin() + i);
                    enemies[k].get()->TakeDamage(20);
                    if (enemies[k].get()->GetHealth() <= 0) {
                        enemies.erase(enemies.begin() + k);
                        std::cout << "Enemy defeated" << std::endl;
                    }
                    break;
                }
            }
        }
    }
}