#include "Game.h"
#include <vector>

Game::Game() :
	mWindow("Game Window", sf::Vector2u(800, 600)), mPlayer(mWindow.GetMWindow()) {
	mWindow.GetMWindow()->setVerticalSyncEnabled(true);
    mWindow.GetMWindow()->setKeyRepeatEnabled(false);
};

Game::~Game(){}

void Game::HandleInput(){
	sf::Event event;
	while (mWindow.GetMWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mWindow.FinishWindow();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
			mWindow.ToggleFullscreen();
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
                Bullet* bullet = new Bullet(mWindow.GetMWindow(), mPlayer.GetPosition(), mPlayer.GetSprite()->getRotation());
                projectiles.push_back(bullet);
            }
        }
	}

    if (animFlags.upPressed) {
        mPlayer.MoveObject(sf::Vector2f(0.f, -mPlayer.GetSpeed() * mElapsed));
        // std::cout << "shape Y coord: " << mPlayer.GetPosition().y << std::endl;
    }
    if (animFlags.downPressed) {
        mPlayer.MoveObject(sf::Vector2f(0.f, mPlayer.GetSpeed() * mElapsed));
        //std::cout << "shape Y coord: " << mPlayer.GetPosition().y << std::endl;
    }
    if (animFlags.leftPressed) {
        mPlayer.MoveObject(sf::Vector2f(-mPlayer.GetSpeed() * mElapsed, 0.f));
        //std::cout << "shape X coord: " << mPlayer.GetPosition().x << std::endl;
    }
    if (animFlags.rightPressed) {
        mPlayer.MoveObject(sf::Vector2f(mPlayer.GetSpeed() * mElapsed, 0.f));
        //std::cout << "shape X coord: " << mPlayer.GetPosition().x << std::endl;
    }
}

void Game::Update() {
    mPlayer.Update(mWindow.GetMWindow(), mElapsed);
    for (Bullet* bullet : projectiles) {
        bullet->Update(mWindow.GetMWindow(), mElapsed);
    }

    sf::View view = mWindow.GetMWindow()->getView();
    sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());

    for (int i = 0; i < projectiles.size(); ++i) {
        if (!(viewRect.contains(projectiles[i]->GetPosition()))) {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
            std::cout << "Projectile deleted" << std::endl;
        }
    }
    
	RestartClock();
}

void Game::Render() {
	mWindow.BeginDraw();
	mWindow.Draw(*mPlayer.GetSprite());
    for (Bullet* bullet : projectiles) {
        mWindow.Draw(*bullet->GetSprite());
    }
	mWindow.EndDraw();
}

void Game::RestartClock() {
	mElapsed = mClock.restart().asSeconds();
}


float Game::GetElapsed() {
	return mElapsed;
}

Window* Game::GetWindow() {
	return &mWindow;
}