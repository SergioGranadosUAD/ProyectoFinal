#include "Game.h"
#include <vector>

Game::Game() :
	mWindow(new Window("Game Window", sf::Vector2u(800, 600))), mPlayer(new Player(mWindow.get()->GetMWindow())) {
	mWindow.get()->GetMWindow()->setVerticalSyncEnabled(true);
    mWindow.get()->GetMWindow()->setKeyRepeatEnabled(false);
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
                std::shared_ptr<Bullet> bullet(new Bullet(mWindow.get()->GetMWindow(), mPlayer.get()->GetPosition(), mPlayer.get()->GetSprite()->getRotation()));
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

    sf::View view = mWindow.get()->GetMWindow()->getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    for (int i = 0; i < projectiles.size(); ++i) {
        if (!(viewRect.contains(projectiles[i]->GetPosition()))) {
            std::cout << "Shared count" << projectiles[i].use_count() << std::endl;
            projectiles.erase(projectiles.begin() + i);
            std::cout << "Projectile deleted" << std::endl;
        }
    }
    
	RestartClock();
}

void Game::Render() {
	mWindow.get()->BeginDraw();
	mWindow.get()->Draw(*mPlayer.get()->GetSprite());
    for (auto bullet : projectiles) {
        mWindow.get()->Draw(*bullet->GetSprite());
    }
	mWindow.get()->EndDraw();
}

void Game::RestartClock() {
	mElapsed = mClock.restart().asSeconds();
}


float Game::GetElapsed() {
	return mElapsed;
}

Window* Game::GetWindow() {
	return mWindow.get();
}