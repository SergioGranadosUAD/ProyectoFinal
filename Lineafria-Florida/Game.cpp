#include "Game.h"

/************************************
* @method:   Game
* @access:   public
* @return    Constructor
* @brief:    Constructor de la clase Game, establece los valores que llevará el juego y crea los elementos necesarios para su funcionamiento.
* @details:  Sin detalles.
*************************************/

Game::Game(std::weak_ptr<Window> window, std::weak_ptr<float> elapsed, const std::string& levelName) {
    mWindow = window.lock();
    mRenderWindow = mWindow->GetMWindow();
    mElapsed = elapsed.lock();
    mFloorLayer = std::make_unique<TileMap>();
    mWallLayer = std::make_unique<TileMap>();

    mGameFinished = false;
    mCurrentLevelName = levelName;

    mPauseMenu = std::make_unique<PauseMenu>(mWindow, mRenderWindow);

    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        mView = std::make_shared<sf::View>(windowPtr->getView());
        mView->setCenter(sf::Vector2f(windowPtr->getSize().x * .5f, windowPtr->getSize().y * .5f));
        mView->zoom(.40f);
        windowPtr->setView(*mView);
    }

    mPlayer = std::make_unique<Player>(mRenderWindow, mView);
    mHud = std::make_unique<HUD>(mWindow, mRenderWindow, mView, mPlayer->GetMaxAmmo());

    LevelData level = LoadLevel(levelName);

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

};

Game::~Game(){

}

/************************************
* @method:   HandleInput
* @access:   public
* @return    void
* @brief:    Este método se encarga de procesar la entrada por parte del usuario.
* @details:  Presenta varios casos para diversas teclas oprimidas por el usuario.
*************************************/
void Game::HandleInput(){
    if (mPauseMenu->GameResumed()) {
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
                    case sf::Keyboard::Escape:
                        animFlags.upPressed = false;
                        animFlags.downPressed = false;
                        animFlags.leftPressed = false;
                        animFlags.rightPressed = false;
                        mPauseMenu->CenterElements(mView->getCenter());
                        mPauseMenu->PauseGame();
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

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (!mPlayer->IsReloading()) {
                        std::shared_ptr<Bullet> bullet(new Bullet(mRenderWindow, mElapsed, *mPlayer->GetPosition().lock(), mPlayer.get()->GetSprite()->getRotation(), BULLET_ID(ALLIED)));
                        projectiles.push_back(bullet);
                        mPlayer->ShootWeapon();
                        mHud->SubstractBullet();
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
        }
    }
    else {
        mPauseMenu->HandleInput();
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
    if (mPauseMenu->GameResumed()) {
        //Primero se revisan las colisiones del jugador, después se hace su update
        for (const auto& wall : mWallCollisions) {
            CheckPlayerCollisions(wall);
        }

        mPlayer->Update();
        mHud->Update();

        if (mPlayer->IsReloading() && mPlayer->GetReloadCooldown() > mPlayer->GetReloadTime()) {
            mHud->ReloadWeapon();
            mPlayer->SetAmmunition(mPlayer->GetMaxAmmo());
        }


        for (const auto& bullet : projectiles) {
            bullet->Update();
        }

        for (const auto& enemy : enemies) {
            enemy->ResetVelocity();
            enemy->Update();

            for (const auto& enemy2 : enemies) {
                if (enemy != enemy2) {
                    CheckEnemyOnEnemyCollisions(enemy, enemy2);
                }
            }

            for (const auto& wall : mWallCollisions) {
                CheckEnemyCollisions(enemy, wall);
            }

            enemy->MoveObject(enemy->GetVelocity());

            //Ataque cuerpo a cuerpo hacia el jugador.
            if (enemy->GetHitbox().intersects(mPlayer->GetHitbox()) && enemy->GetCooldownTime() > 1000) {
                std::cout << "Melee attack on player." << std::endl;
                mPlayer.get()->TakeDamage(20);
                enemy->RestartCooldown();
            }
            if (enemy->HasBeenStartled() && enemy->GetType() == ENEMY_TYPE::SHOOTER && enemy->GetCooldownTime() > 2000) {
                std::shared_ptr<Bullet> enemyBullet = std::make_shared<Bullet>(mRenderWindow, mElapsed, enemy->GetPosition(), enemy->GetRotation(), BULLET_ID::ENEMY);
                projectiles.push_back(enemyBullet);
                enemy->RestartCooldown();
            }
        }

        CheckProjectileCollision();

        //Se verifica si el jugador sigue vivo, de lo contrario reinicia el juego.
        if (mPlayer->GetHealth() <= 0) {
            std::cout << "Player death." << std::endl;
            ChangeLevel(mCurrentLevelName);
        }
        if (mWinCondition && mPlayer->GetHitbox().intersects(mNextLevelZone->getGlobalBounds())) {
            ChangeLevel(mNextLevelName);
        }
    }
    else {
        mPauseMenu->Update();
        if (mPauseMenu->GameFinished()) {
            mGameFinished = true;
        }
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
        mWindow->Draw(bullet->mHitbox);
    }
    for (auto& enemy : enemies) {
        mWindow->Draw(*enemy.get()->GetSprite());
        mWindow->Draw(enemy->mHitbox);
    }

    //Activar para probar posiciones de muros.
    for (auto& coll : mWallCollisions) {
        mWindow->Draw(*coll);
    }

    if (mWinCondition) {
        mWindow->Draw(*mNextLevelZone);
    }

    mHud->Render();

    if (!mPauseMenu->GameResumed()) {
        mPauseMenu->Render();
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
void Game::ChangeLevel(const std::string& levelname) {
    mPlayer.reset();
    mFloorLayer.reset();
    mWallLayer.reset();
    mPlayer = std::make_unique<Player>(mRenderWindow, mView);
    mFloorLayer = std::make_unique<TileMap>();
    mWallLayer = std::make_unique<TileMap>();
    mClock.restart();
    *mElapsed = 0.f;
    animFlags = {};
    projectiles.clear();
    enemies.clear();
    mWallCollisions.clear();

    LevelData level = LoadLevel(levelname);

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
        }
        else {
            //Se comprueba si un proyectil es enemigo y colisiona con el jugador.
            if (projectiles[i]->GetHitbox().intersects(mPlayer->GetHitbox()) && projectiles[i]->GetID() == BULLET_ID::ENEMY) {
                projectiles.erase(projectiles.begin() + i);
                mPlayer.get()->TakeDamage(20);
                break;
            }

            bool listUpdated = false;

            //Se comprueba si el proyectil es del jugador y colisiona con un enemigo.
            for (int k = 0; k < enemies.size(); ++k) {
                if (projectiles[i]->GetHitbox().intersects(enemies[k]->GetHitbox()) && projectiles[i].get()->GetID() == BULLET_ID::ALLIED) {
                    projectiles.erase(projectiles.begin() + i);
                    enemies[k].get()->TakeDamage(20);
                    if (enemies[k].get()->GetHealth() <= 0) {
                        enemies.erase(enemies.begin() + k);
                        std::cout << "Enemy defeated" << std::endl;

                        if (enemies.size() == 0) {
                            mWinCondition = true;
                        }
                    }
                    listUpdated = true;
                    break;
                }
            }

            if (listUpdated) {
                break;
            }

            //Se comprueba si el proyectil colisiona con un muro.
            for (const auto& wall : mWallCollisions) {
                sf::FloatRect wallBounds = wall->getGlobalBounds();
                if (wallBounds.intersects(projectiles[i]->GetHitbox())) {
                    projectiles.erase(projectiles.begin() + i);
                    break;
                }
            }
        }
    }
}

void Game::CheckPlayerCollisions(std::shared_ptr<sf::RectangleShape> wall) {
    sf::FloatRect playerBounds = mPlayer->GetHitbox();
    sf::FloatRect wallBounds = wall->getGlobalBounds();
    sf::FloatRect nextPos = playerBounds;


    nextPos.left += mPlayer->GetVelocity().x;
    nextPos.top += mPlayer->GetVelocity().y;
    if (wallBounds.intersects(nextPos)) {
        //std::cout << "Player intersecting wall" << std::endl;
        mPlayer->CheckPlayerBounds(playerBounds, wallBounds);
    }
}

void Game::CheckEnemyCollisions(std::shared_ptr<Enemy> enemy, std::shared_ptr<sf::RectangleShape> wall) {
    sf::FloatRect enemyBounds = enemy->GetHitbox();
    sf::FloatRect wallBounds = wall->getGlobalBounds();
    sf::FloatRect nextPos = enemyBounds;


    nextPos.left += enemy->GetVelocity().x;
    nextPos.top += enemy->GetVelocity().y;
    if (wallBounds.intersects(nextPos)) {
        //std::cout << "Enemy intersecting wall" << std::endl;
        enemy->CheckEnemyBounds(enemyBounds, wallBounds);
    }
}

void Game::CheckEnemyOnEnemyCollisions(std::shared_ptr<Enemy> enemy1, std::shared_ptr<Enemy> enemy2) {
    sf::FloatRect firstEnemyBounds = enemy1->GetHitbox();
    sf::FloatRect secondEnemyBounds = enemy2->GetHitbox();
    sf::FloatRect nextPos = firstEnemyBounds;


    nextPos.left += enemy1->GetVelocity().x;
    nextPos.top += enemy1->GetVelocity().y;
    if (secondEnemyBounds.intersects(nextPos)) {
        //std::cout << "Enemy intersecting enemy" << std::endl;
        enemy1->CheckEnemyBounds(firstEnemyBounds, secondEnemyBounds);
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

        mNextLevelName = data[levelName]["nextLevelName"];
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
            shape->setOrigin(shapeBounds.width * .5f, shapeBounds.height * .5f);
            shape->setFillColor(sf::Color::Blue);
            shape->setPosition(sf::Vector2f(levelData.spawnPos.x + obj["posX"], levelData.spawnPos.y + obj["posY"]));

            mWallCollisions.push_back(shape);
        }

        for (auto obj : data[levelName]["enemies"]) {
            sf::Vector2f enemyPosition;
            ENEMY_TYPE type;
            enemyPosition.x = levelData.spawnPos.x + obj["posX"];
            enemyPosition.y = levelData.spawnPos.y + obj["posY"];
            type = (ENEMY_TYPE)obj["enemyType"];

            std::cout << "Enemy spawned" << std::endl;
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(mRenderWindow, mElapsed, mPlayer->GetPosition(), enemyPosition, type);
            enemies.push_back(enemy);
        }

        mNextLevelZone = std::make_unique<sf::RectangleShape>(sf::Vector2f(data[levelName]["winZone"]["width"], data[levelName]["winZone"]["height"]));
        sf::Vector2f winZonePosition;
        sf::FloatRect zoneBounds = mNextLevelZone->getGlobalBounds();
        winZonePosition.x = levelData.spawnPos.x + data[levelName]["winZone"]["posX"];
        winZonePosition.y = levelData.spawnPos.y + data[levelName]["winZone"]["posY"];
        mNextLevelZone->setOrigin(zoneBounds.width * .5f, zoneBounds.height * .5f);
        mNextLevelZone->setFillColor(sf::Color(200, 0, 0, 200));
        mNextLevelZone->setOutlineColor(sf::Color::Red);
        mNextLevelZone->setOutlineThickness(1.0f);
        mNextLevelZone->setPosition(winZonePosition);

        return levelData;
    }
    catch (json::type_error& e) {
        std::cerr << e.what() << std::endl;
    }
    
}

void Game::ResetView() {
    if (!mRenderWindow.expired()) {
        std::shared_ptr<sf::RenderWindow> windowPtr = mRenderWindow.lock();
        *mView = windowPtr->getDefaultView();
        windowPtr->setView(*mView);
    }
    
}