class ScrollingBackground {
public:
    sf::Texture texture;
    sf::Sprite sprite1, sprite2;
    const float scrollSpeed = 150.0f; // Adjust scrolling speed
    float windowWidth;

    ScrollingBackground(float width) : windowWidth(width) {
        // Load the texture
        if (!texture.loadFromFile("../ressources/sprites/gdbackground.png")) {
            // Handle loading error
        }

        // Set texture to sprites
        sprite1.setTexture(texture);
        sprite2.setTexture(texture);

        // Initially position the second sprite adjacent to the first
        // considering the window's width if necessary
        repositionSprites();
    }

    void update(float deltaTime) {
        // Scroll the sprites left
        sprite1.move(-scrollSpeed * deltaTime, 0);
        sprite2.move(-scrollSpeed * deltaTime, 0);

        // If a sprite completely moves out of view (left of the screen), reset its position
        if (sprite1.getPosition().x + texture.getSize().x < 0) {
            sprite1.setPosition(sprite2.getPosition().x + texture.getSize().x, 0);
        }
        if (sprite2.getPosition().x + texture.getSize().x < 0) {
            sprite2.setPosition(sprite1.getPosition().x + texture.getSize().x, 0);
        }

        // Ensure continuous coverage
        repositionSprites();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite1);
        window.draw(sprite2);
    }

private:
    void repositionSprites() {
        // Ensure the sprites cover the entire window width continuously
        if (sprite1.getPosition().x + texture.getSize().x < windowWidth) {
            sprite2.setPosition(sprite1.getPosition().x + texture.getSize().x, 0);
        }
        if (sprite2.getPosition().x + texture.getSize().x < windowWidth) {
            sprite1.setPosition(sprite2.getPosition().x + texture.getSize().x, 0);
        }
    }
};
