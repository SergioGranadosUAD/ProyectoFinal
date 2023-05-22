#include <sfml/Graphics.hpp>

struct AnimFlags {
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
};

void Update(sf::RenderWindow& window, sf::CircleShape& shape, sf::Event& event, AnimFlags& animFlags, sf::Vector2f& position, const int& PLAYER_SPEED, const float& deltaTime);
void Render(sf::RenderWindow& window, sf::CircleShape& shape);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game loop test");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);

    const int PLAYER_SPEED = 1;
    sf::Vector2f position;

    AnimFlags animFlags;
    position.x = window.getSize().x * .5f;
    position.y = window.getSize().y * .5f;

    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);
    sf::FloatRect spriteSize = shape.getGlobalBounds();
    shape.setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);

    sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = timer.restart().asMilliseconds();
        Update(window, shape, event, animFlags, position, PLAYER_SPEED, deltaTime);
        Render(window, shape);
    }

    return 0;
}

void Update(sf::RenderWindow& window, sf::CircleShape& shape, sf::Event& event, AnimFlags& animFlags, sf::Vector2f& position,const int& PLAYER_SPEED, const float& deltaTime) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            animFlags.upPressed = true;
            break;
        case sf::Keyboard::Down:
            animFlags.downPressed = true;
            break;
        case sf::Keyboard::Left:
            animFlags.leftPressed = true;
            break;
        case sf::Keyboard::Right:
            animFlags.rightPressed = true;
            break;
        default:
            break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            animFlags.upPressed = false;
            break;
        case sf::Keyboard::Down:
            animFlags.downPressed = false;
            break;
        case sf::Keyboard::Left:
            animFlags.leftPressed = false;
            break;
        case sf::Keyboard::Right:
            animFlags.rightPressed = false;
            break;
        default:
            break;
        }
    }

    if (animFlags.upPressed) {
        position.y -= PLAYER_SPEED * deltaTime;
    }
    if (animFlags.downPressed) {
        position.y += PLAYER_SPEED * deltaTime;
    }
    if (animFlags.leftPressed) {
        position.x -= PLAYER_SPEED * deltaTime;
    }
    if (animFlags.rightPressed) {
        position.x += PLAYER_SPEED * deltaTime;
    }

    if (position.x < 0) {
        position.x = window.getSize().x;
    }
    if (position.x > (int)window.getSize().x) {
        position.x = 0;
    }
    if (position.y < 0) {
        position.y = window.getSize().y;
    }
    if (position.y > (int)window.getSize().y) {
        position.y = 0;
    }

    shape.setPosition(position);
}

void Render(sf::RenderWindow& window, sf::CircleShape& shape) {
    window.clear();
    window.draw(shape);
    window.display();
}