
class ScrollingBackground {
public:
    sf::Texture texture;
    sf::Sprite sprite1, sprite2;
    const float scrollSpeed = 100.0f; // Adjust scrolling speed

    ScrollingBackground() {
        // Load the texture
        if (!texture.loadFromFile("../ressources/sprites/gdbackground.png")) {
            // Handle loading error
        }

        // Set texture to sprites
        sprite1.setTexture(texture);
        sprite2.setTexture(texture);

        // Position the second sprite to the right of the first one
        sprite2.setPosition(texture.getSize().x, 0);
    }

    void update(float deltaTime) {
        // Scroll the sprites left
        sprite1.move(-scrollSpeed * deltaTime, 0);
        sprite2.move(-scrollSpeed * deltaTime, 0);

        // If a sprite completely moves out of view, reset its position
        if (sprite1.getPosition().x + texture.getSize().x < 0) {
            sprite1.setPosition(sprite2.getPosition().x + texture.getSize().x, 0);
        }
        if (sprite2.getPosition().x + texture.getSize().x < 0) {
            sprite2.setPosition(sprite1.getPosition().x + texture.getSize().x, 0);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite1);
        window.draw(sprite2);
    }
};



