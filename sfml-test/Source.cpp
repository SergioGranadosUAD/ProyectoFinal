#include <sfml/Graphics.hpp>

void Update(sf::RenderWindow& window, sf::CircleShape& shape, sf::Event& event, bool& upPressed, bool& downPressed, bool& leftPressed, bool& rightPressed, int& posX, int& posY, const int& PLAYER_SPEED);
void Render(sf::RenderWindow& window, sf::CircleShape& shape);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game loop test");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);

    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    const int PLAYER_SPEED = 5;

    int posX = window.getSize().x / 2.;
    int posY = window.getSize().y / 2.;

    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);
    sf::FloatRect spriteSize = shape.getGlobalBounds();
    shape.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);

    //sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Update(window, shape, event, upPressed, downPressed, leftPressed, rightPressed, posX, posY, PLAYER_SPEED);
        Render(window, shape);
    }

    return 0;
}

void Update(sf::RenderWindow& window, sf::CircleShape& shape, sf::Event& event, bool& upPressed, bool& downPressed, bool& leftPressed, bool& rightPressed, int& posX, int& posY,const int& PLAYER_SPEED ) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            upPressed = true;
            break;
        case sf::Keyboard::Down:
            downPressed = true;
            break;
        case sf::Keyboard::Left:
            leftPressed = true;
            break;
        case sf::Keyboard::Right:
            rightPressed = true;
            break;
        default:
            break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            upPressed = false;
            break;
        case sf::Keyboard::Down:
            downPressed = false;
            break;
        case sf::Keyboard::Left:
            leftPressed = false;
            break;
        case sf::Keyboard::Right:
            rightPressed = false;
            break;
        default:
            break;
        }
    }

    if (upPressed) {
        posY -= PLAYER_SPEED;
    }
    if (downPressed) {
        posY += PLAYER_SPEED;
    }
    if (rightPressed) {
        posX += PLAYER_SPEED;
    }
    if (leftPressed) {
        posX -= PLAYER_SPEED;
    }

    if (posX < 0) {
        posX = window.getSize().x;
    }
    if (posX > (int)window.getSize().x) {
        posX = 0;
    }
    if (posY < 0) {
        posY = window.getSize().y;
    }
    if (posY > (int)window.getSize().y) {
        posY = 0;
    }

    shape.setPosition(posX, posY);
}

void Render(sf::RenderWindow& window, sf::CircleShape& shape) {
    window.clear();
    window.draw(shape);
    window.display();
}