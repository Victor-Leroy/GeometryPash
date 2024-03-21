#include <SFML/Graphics.hpp>

class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float verticalVelocity = 0.0f;
    bool isJumping = false;

    Player() {
         // Load the texture
        if (!texture.loadFromFile("./sprites/character.png")) { // Replace "character.png" with your image file
            // Handle error
        }

        // Set the texture to the sprite
        sprite.setTexture(texture);

        // Optionally, resize the sprite
        // sprite.setScale(sf::Vector2f(0.5f, 0.5f)); // Example scale

        // Set the starting position of the sprite
        shape.setPosition(100.0f, 500.0f); // Starting position
    }

    void update(float deltaTime) {
        const float gravity = 1000.0f; // Pixels per second^2
        const float jumpVelocity = -500.0f; // Initial jump velocity

        // Apply gravity if in the air
        if (!isOnGround()) {
            verticalVelocity += gravity * deltaTime;
        } else if (isJumping) {
            verticalVelocity = jumpVelocity;
            isJumping = false;
        }

        // Update position
        shape.move(0.0f, verticalVelocity * deltaTime);

        // Example ground check
        if (shape.getPosition().y >= 500.0f) {
            shape.setPosition(shape.getPosition().x, 500.0f);
            verticalVelocity = 0.0f;
        }
    }

    bool isOnGround() {
        return shape.getPosition().y >= 500.0f; // Simplified ground check
    }

    void jump() {
        if (isOnGround()) {
            isJumping = true;
        }
    }
};

// Example usage
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    Player player;
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

        window.clear();
        window.draw(player.sprite);
        window.display();
    }

    return 0;
}
