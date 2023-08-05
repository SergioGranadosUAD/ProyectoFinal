#include "Game.h"

/************************************
* @method:   Game
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Game, establece los valores que llevará el juego y crea los elementos necesarios para su funcionamiento.
* @details:  Sin detalles.
*************************************/

Game::Game(std::weak_ptr<Window> window, std::weak_ptr<float> elapsed) {
    mWindow = window.lock();
    mRenderWindow = mWindow->GetMWindow();
    mElapsed = elapsed.lock();
    mFloorLayer = std::make_unique<TileMap>();
    mWallLayer = std::make_unique<TileMap>();

    LevelData level = LoadLevel("Level1");

    if (!mFloorLayer->Load("TileSet.png", sf::Vector2u(32, 32), level.layerTiles, level.width, level.height)) {
        std::cout << "Failed to load floor layer" << std::endl;
    }
    if (!mWallLayer->Load("TileSet.png", sf::Vector2u(32, 32), level.layerWalls, level.width, level.height)) {
        std::cout << "Failed to load wall layer" << std::endl;
    }

    
    mFloorLayer->setPosition(sf::Vector2f(level.spawnPos));
    mFloorLayer->setOrigin(sf::Vector2f(level.width * 16, level.height * 16));
    mWallLayer->setPosition(sf::Vector2f(level.spawnPos));
    mWallLayer->setOrigin(sf::Vector2f(level.width * 16, level.height * 16));

    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        windowPtr->setVerticalSyncEnabled(true);
        windowPtr->setKeyRepeatEnabled(false);
        mView = std::make_shared<sf::View>(windowPtr->getView());
        mView->setCenter(sf::Vector2f(windowPtr->getSize().x*.5f, windowPtr->getSize().y*.5f));
        mView->zoom(.40f);
        windowPtr->setView(*mView);
    }

    mPlayer = std::make_unique<Player>(mRenderWindow, mView);
    

    /*std::shared_ptr<Enemy> enemyPtr(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(100, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr);

    std::shared_ptr<Enemy> enemyPtr2(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(400, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr2);

    std::shared_ptr<Enemy> enemyPtr3(std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer.get()->GetPosition(), sf::Vector2f(700, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr3);*/
};

Game::~Game(){}

/************************************
* @method:   HandleInput
* @access:   public
* @return    void
* @brief:    Este método se encarga de procesar la entrada por parte del usuario.
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
                    std::shared_ptr<Bullet> bullet(new Bullet(mRenderWindow, mElapsed, *mPlayer->GetPosition().lock(), mPlayer.get()->GetSprite()->getRotation(), BULLET_ID(ALLIED)));
                    projectiles.push_back(bullet);
                }
            }
        }

        mPlayer->ResetVelocity();
        //Mueve al jugador dependiendo de las banderas que se encuentren encedidas.
        if (animFlags.upPressed) {
            mPlayer->AddVelocity(sf::Vector2f(0.f, -mPlayer->GetSpeed() * *mElapsed));
        }
        if (animFlags.downPressed) {
            mPlayer->AddVelocity(sf::Vector2f(0.f, mPlayer->GetSpeed() * *mElapsed));
        }
        if (animFlags.leftPressed) {
            mPlayer->AddVelocity(sf::Vector2f(-mPlayer->GetSpeed() * *mElapsed, 0.f));
        }
        if (animFlags.rightPressed) {
            mPlayer->AddVelocity(sf::Vector2f(mPlayer->GetSpeed() * *mElapsed, 0.f));
        }
        mPlayer->MoveObject(mPlayer->GetVelocity());
    }
	
    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        windowPtr->setView(*mView);
    }
}

/************************************
* @method:   Update
* @access:   public
* @return    void
* @brief:    Método que actualiza el juego de forma constante, así como todos los elementos que requieran actualizarse.
* @details:  Sin detalles.
*************************************/
void Game::Update() {

    //Actualización de todas las entidades en el juego.
    mPlayer->Update();
    for (auto bullet : projectiles) {
        bullet->Update();
    }
    for (auto enemy : enemies) {
        enemy->Update();

        //Ataque cuerpo a cuerpo hacia el jugador.
        if (enemy->GetSprite()->getGlobalBounds().intersects(mPlayer->GetHitbox()) && enemy->GetCooldownTime() > 2000) {
            std::cout << "Melee attack on player." << std::endl;
            mPlayer.get()->TakeDamage(20);
            enemy->RestartCooldown();
        }
    }

    for (auto wall : mWallCollisions) {
        sf::FloatRect wallRect = wall->getGlobalBounds();
        if (mPlayer->GetHitbox().intersects(wallRect)) {
            std::cout << "Is intersecting wall" << std::endl;
            mPlayer->CheckPlayerBounds(wallRect);
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
* @brief:    Este método dibuja todas las entidades en la ventana.
* @details:  Sin detalles.
*************************************/
void Game::Render() {
	mWindow->BeginDraw();
    mWindow->Draw(*mFloorLayer);
    mWindow->Draw(*mWallLayer);
	mWindow->Draw(*mPlayer->GetSprite());
    mWindow->Draw(mPlayer->mHitbox);
    for (auto& bullet : projectiles) {
        mWindow->Draw(*bullet.get()->GetSprite());
    }
    for (auto& enemy : enemies) {
        mWindow->Draw(*enemy.get()->GetSprite());
    }

    for (auto& coll : mWallCollisions) {
        mWindow->Draw(*coll);
    }

	mWindow->EndDraw();
}

/************************************
* @method:   RestartClock
* @access:   public
* @return    void
* @brief:    Este método reinicia el reloj y le asigna el tiempo que ha pasado desde el último reinicio a la variable mElapsed.
* @details:  Sin detalles.
*************************************/
void Game::RestartClock() {
	*mElapsed = mClock.restart().asSeconds();
}

/************************************
* @method:   GetElapsed
* @access:   public
* @return    weak_ptr<float>
* @brief:    Este método devuelve el tiempo transcurrido desde el último reinicio del reloj.
* @details:  Sin detalles.
*************************************/
std::weak_ptr<float> Game::GetElapsed() {
	return mElapsed;
}

/************************************
* @method:   GetWindow
* @access:   public
* @return    weak_ptr<Window>
* @brief:    Este método devuelve un puntero a la ventana para que pueda ser ocupada.
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
* @brief:    Este método reinicia el nivel a su estado inicial, para que se pueda volver a jugar.
* @details:  Sin detalles.
*************************************/
void Game::RestartGame() {
    mPlayer.reset();
    mPlayer = std::make_unique<Player>(mRenderWindow, mView);
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
* @brief:    Este método revisa si los proyectiles colisionan con jugador o un enemigo, y realiza los comportamientos apropiados.
* @details:  Sin detalles.
*************************************/
void Game::CheckProjectileCollision() {

    sf::FloatRect viewRect(mView->getCenter() - mView->getSize() / 2.f, mView->getSize());

    //Iteración de proyectiles.
    for (int i = 0; i < projectiles.size(); ++i) {

        //Se eliminan aquellos proyectiles que salen de la pantalla.
        if (!(viewRect.contains(projectiles[i]->GetPosition()))) {
            projectiles.erase(projectiles.begin() + i);
            //std::cout << "Projectile deleted" << std::endl;
        }
        else {
            //Se comprueba si un proyectil es enemigo y colisiona con el jugador.
            if (projectiles[i].get()->GetSprite()->getGlobalBounds().intersects(mPlayer->GetHitbox()) && projectiles[i].get()->GetID() == BULLET_ID::ENEMY) {
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

LevelData Game::LoadLevel(const std::string& levelName) {
    try {
        LevelData levelData;
        json data;
        std::ifstream levelFile{ "Levels/" + levelName + ".json" };

        if (!levelFile) {
            std::cout << "Failed to open file " << levelName << std::endl;
        }

        data = json::parse(levelFile);


        levelData.spawnPos.x = data[levelName]["spawnPosX"];
        levelData.spawnPos.y = data[levelName]["spawnPosY"];
        levelData.width = data[levelName]["mapWidth"];
        levelData.height = data[levelName]["mapHeight"];

        for (int i : data[levelName]["floorLayer"]) {
            levelData.layerTiles.push_back(i);
        }

        for (int i : data[levelName]["wallLayer"]) {
            levelData.layerWalls.push_back(i);
        }

        for (auto obj : data[levelName]["hitboxes"]) {
            std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(obj["width"], obj["height"]));
            sf::FloatRect shapeBounds = shape->getGlobalBounds();
            shape->setOrigin(shapeBounds.width / 2, shapeBounds.height / 2);
            shape->setPosition(sf::Vector2f(levelData.spawnPos.x + obj["posX"], levelData.spawnPos.y + obj["posY"]));

            mWallCollisions.push_back(shape);
        }

        return levelData;
    }
    catch (json::type_error& e) {
        std::cerr << e.what() << std::endl;
    }
    
}