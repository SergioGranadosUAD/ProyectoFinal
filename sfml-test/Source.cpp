#include <sfml/Graphics.hpp>
#include <math.h>
#include <iostream>

const int PLAYER_SPEED = 500;
const float PI = 3.1416;

struct AnimFlags {
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;
};

void Update(sf::RenderWindow& window, sf::RectangleShape& shape, sf::CircleShape& cursor, sf::Event& event, AnimFlags& animFlags, sf::Vector2f& shapePos, sf::Vector2i& cursorPos, const int& PLAYER_SPEED, const float& deltaTime);
void Render(sf::RenderWindow& window, sf::RectangleShape& shape, sf::CircleShape& cursor);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game loop test");
    window.setVerticalSyncEnabled(true);
    //window.setKeyRepeatEnabled(true);

    sf::Vector2f shapePos;
    sf::Vector2i cursorPos;

    AnimFlags animFlags;
    shapePos.x = window.getSize().x * .5f;
    shapePos.y = window.getSize().y * .5f;

    cursorPos.x = window.getSize().x * .5f;
    cursorPos.y = window.getSize().y * .5f;

    sf::Vector2f rectangleSize{40.f,30.f};

    sf::RectangleShape shape(rectangleSize);
    shape.setFillColor(sf::Color::Green);
    sf::FloatRect spriteSize = shape.getGlobalBounds();
    shape.setOrigin(spriteSize.width * .5f, spriteSize.height * .5f);

    sf::CircleShape cursor(5.f);
    cursor.setFillColor(sf::Color::Red);
    sf::FloatRect cursorSize = cursor.getGlobalBounds();
    cursor.setOrigin(cursorSize.width * .5f, cursorSize.height * .5f);

    sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            float deltaTime = timer.restart().asSeconds();
            Update(window, shape, cursor, event, animFlags, shapePos, cursorPos, PLAYER_SPEED, deltaTime);
            Render(window, shape, cursor);
        }
    }

    return 0;
}

void Update(sf::RenderWindow& window, sf::RectangleShape& shape, sf::CircleShape& cursor, sf::Event& event, AnimFlags& animFlags, sf::Vector2f& shapePos, sf::Vector2i& cursorPos,const int& PLAYER_SPEED, const float& deltaTime) {
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

    if (animFlags.upPressed) {
        shapePos.y -= PLAYER_SPEED * deltaTime;
        std::cout << "shape Y coord: " << shapePos.y << std::endl;
    }
    if (animFlags.downPressed) {
        shapePos.y += PLAYER_SPEED * deltaTime;
        std::cout << "shape Y coord: " << shapePos.y << std::endl;
    }
    if (animFlags.leftPressed) {
        shapePos.x -= PLAYER_SPEED * deltaTime;
        std::cout << "shape X coord: " << shapePos.x << std::endl;
    }
    if (animFlags.rightPressed) {
        shapePos.x += PLAYER_SPEED * deltaTime;
        std::cout << "shape X coord: " << shapePos.x << std::endl;
    }

    if (shapePos.x < 0) {
        shapePos.x = window.getSize().x;
    }
    if (shapePos.x > (int)window.getSize().x) {
        shapePos.x = 0;
    }
    if (shapePos.y < 0) {
        shapePos.y = window.getSize().y;
    }
    if (shapePos.y > (int)window.getSize().y) {
        shapePos.y = 0;
    }
    
    cursorPos = sf::Mouse::getPosition(window);
    sf::Vector2f cursorFloatPos = window.mapPixelToCoords(cursorPos);

    cursor.setPosition(cursorFloatPos);
    shape.setPosition(shapePos);
    shape.setRotation(atan2f(cursorFloatPos.y - shapePos.y, cursorFloatPos.x - shapePos.x) * (180 / PI));
}

void Render(sf::RenderWindow& window, sf::RectangleShape& shape, sf::CircleShape& cursor) {
    window.clear();
    window.draw(shape);
    window.draw(cursor);
    window.display();
}