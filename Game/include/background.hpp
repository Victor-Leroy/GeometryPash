
class ScrollingBackground {
public:

    ScrollingBackground(const std::string& texturePath, float speed, unsigned int windowWidth)
        : scrollSpeed(speed) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Unable to load background texture");
        }

        texture.setRepeated(true); // Enable texture repeating

        // Calculate how many sprites are needed to cover the entire window width
        unsigned int spriteCount = windowWidth / texture.getSize().x + 1;

        // Create and position the sprites
        for (unsigned int i = 0; i <= spriteCount; ++i) {
            sf::Sprite sprite(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)); // Set the texture rectangle
            sprite.setPosition(static_cast<float>(i * texture.getSize().x), 0);
            sprites.push_back(sprite);
        }
    }

    void update(float deltaTime) {
        // Move each sprite left by scrollSpeed
        for (auto& sprite : sprites) {
            sprite.move(-scrollSpeed * deltaTime, 0);

            // If the sprite is off-screen, reset its position to the right
            if (sprite.getPosition().x + texture.getSize().x < 0) {
                sprite.setPosition(sprites.back().getPosition().x + texture.getSize().x, 0);
                // Move the reset sprite to the back of the vector to maintain ordering
                std::rotate(sprites.begin(), sprites.begin() + 1, sprites.end());
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }

private:
    sf::Texture texture;
    std::vector<sf::Sprite> sprites;
    const float scrollSpeed; // Pixels per second
};
