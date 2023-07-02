#include "Game.h"

Game::Game() :
	mWindow(new Window("Game Window", sf::Vector2u(800, 600))), mPlayer(new Player(mWindow.get()->GetMWindow())), mElapsed(0) {
	mWindow.get()->GetMWindow()->setVerticalSyncEnabled(true);
    mWindow.get()->GetMWindow()->setKeyRepeatEnabled(false);

    std::shared_ptr<Enemy> enemyPtr(new Enemy(mWindow.get()->GetMWindow(), sf::Vector2f(100, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr);

    std::shared_ptr<Enemy> enemyPtr2(new Enemy(mWindow.get()->GetMWindow(), sf::Vector2f(400, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr2);

    std::shared_ptr<Enemy> enemyPtr3(new Enemy(mWindow.get()->GetMWindow(), sf::Vector2f(700, 100), ENEMY_TYPE(CHASER)));
    enemies.push_back(enemyPtr3);
};

Game::~Game(){}

void Game::HandleInput(){
	sf::Event event;
	while (mWindow.get()->GetMWindow()->pollEvent(event)) {
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
                std::shared_ptr<Bullet> bullet(new Bullet(mWindow.get()->GetMWindow(), mPlayer.get()->GetPosition(), mPlayer.get()->GetSprite()->getRotation(), BULLET_ID(ALLIED)));
                projectiles.push_back(bullet);
            }
        }
	}

    if (animFlags.upPressed) {
        mPlayer.get()->MoveObject(sf::Vector2f(0.f, -mPlayer.get()->GetSpeed() * mElapsed));
        // std::cout << "shape Y coord: " << mPlayer.GetPosition().y << std::endl;
    }
    if (animFlags.downPressed) {
        mPlayer.get()->MoveObject(sf::Vector2f(0.f, mPlayer.get()->GetSpeed() * mElapsed));
        //std::cout << "shape Y coord: " << mPlayer.GetPosition().y << std::endl;
    }
    if (animFlags.leftPressed) {
        mPlayer.get()->MoveObject(sf::Vector2f(-mPlayer.get()->GetSpeed() * mElapsed, 0.f));
        //std::cout << "shape X coord: " << mPlayer.GetPosition().x << std::endl;
    }
    if (animFlags.rightPressed) {
        mPlayer.get()->MoveObject(sf::Vector2f(mPlayer.get()->GetSpeed() * mElapsed, 0.f));
        //std::cout << "shape X coord: " << mPlayer.GetPosition().x << std::endl;
    }
}

void Game::Update() {
    mPlayer.get()->Update(mWindow.get()->GetMWindow(), mElapsed);
    for (auto bullet : projectiles) {
        bullet->Update(mWindow.get()->GetMWindow(), mElapsed);
    }
    for (auto enemy : enemies) {
        enemy->Update(mWindow.get()->GetMWindow(), mElapsed, mPlayer.get()->GetPosition());

        if (enemy->GetSprite()->getGlobalBounds().intersects(mPlayer.get()->GetSprite()->getGlobalBounds()) && enemy->GetCooldownTime() > 2000) {
            std::cout << "Melee attack on player." << std::endl;
            mPlayer.get()->TakeDamage(20);
            enemy->RestartCooldown();
        }
    }

    sf::View view = mWindow.get()->GetMWindow()->getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    //Iteración de proyectiles.
    for (int i = 0; i < projectiles.size(); ++i) {
        
        //Se eliminan aquellos proyectiles que salen de la pantalla.
        if (!(viewRect.contains(projectiles[i]->GetPosition()))) {
            projectiles.erase(projectiles.begin() + i);
            std::cout << "Projectile deleted" << std::endl;
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
    
    if (mPlayer.get()->GetHealth() <= 0) {
        std::cout << "Player death." << std::endl;
        RestartGame();
    }

    //Test section
    /*if (timer2s < 120) {
        ++timer2s;
    }
    else {
        std::shared_ptr<Bullet> bullet(new Bullet(mWindow.get()->GetMWindow(), sf::Vector2f(100, 500), 0, BULLET_ID(ENEMY)));
        projectiles.push_back(bullet);
        timer2s = 0;
    }
    */
	RestartClock();
}

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

void Game::RestartClock() {
	mElapsed = mClock.restart().asSeconds();
}


float Game::GetElapsed() {
	return mElapsed;
}

std::weak_ptr<Window> Game::GetWindow() {
    std::weak_ptr<Window> windowPtr = mWindow;
	return windowPtr;
}

void Game::RestartGame() {
    mPlayer.reset();
    mPlayer = std::make_unique<Player>(mWindow.get()->GetMWindow());
    mClock.restart();
    mElapsed = 0.f;
    animFlags = {};
    projectiles.clear();
    enemies.clear();
}