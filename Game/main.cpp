#include "lib.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    Player player;
    ScrollingBackground background;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                player.jump();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        player.update(deltaTime);
        background.update(deltaTime);

        window.clear();
        background.draw(window);
        window.draw(player.sprite); // Draw the sprite instead of the sprite
        window.display();
    }

    return 0;
}


