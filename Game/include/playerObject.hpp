
class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;

    Player() {
         // Load the texture
        if (!texture.loadFromFile("../ressources/sprites/icon.png")) { // Replace "character.png" with your image file
            // Handle error
        }

        // Set the texture to the sprite
        sprite.setTexture(texture);

        // Optionally, resize the sprite
        sprite.setScale(sf::Vector2f(0.5f, 0.5f)); // Example scale

        // Set the starting position of the sprite
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f); // Set the origin to the center of the texture
        sprite.setPosition(300.0f, 500.0f); // Starting position
    }

    void update(float deltaTime) {
        // Apply gravity
        if (!isOnGround() || isJumping) {
            verticalVelocity += gravity * deltaTime;
        }

        // Start jump
        if (isJumping && isOnGround()) {
            verticalVelocity = jumpVelocity;
            isJumping = false;
            isRotating = true;
            totalRotation = 0.0f; // Reset rotation for new jump
        }

        // Handle rotation
        if (isRotating) {
            float rotationStep = rotationSpeed * deltaTime;
            sprite.rotate(rotationStep);
            totalRotation += rotationStep;
            // Check if rotation exceeds or meets the target
            if (totalRotation >= maxRotation) {
                isRotating = false;
                // Adjust for any overshoot beyond the target rotation
                float overshoot = std::fmod(totalRotation, maxRotation);
                sprite.rotate(-overshoot);
            }
        }

        // Update position
        sprite.move(0.0f, verticalVelocity * deltaTime);

        // Example ground check
        if (sprite.getPosition().y >= 500.0f) {
            sprite.setPosition(sprite.getPosition().x, 500.0f);
            verticalVelocity = 0.0f;
        }
    }

    bool isOnGround() {
        return sprite.getPosition().y >= 500.0f; // Simplified ground check
    }

    void jump() {
        if (isOnGround()) {
            isJumping = true;
        }
    }

    bool collidesWith(const Level& level) {
    for (const auto& obstacle : level.obstacles) {
        if ( sprite.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

private:
    
    float verticalVelocity = 0.0f;
    bool isJumping = false;
    bool isRotating = false; // Indicates if the character is currently rotating
    float rotationSpeed = 300.0f; // Speed of rotation in degrees per second
    float totalRotation = 0.0f; // Reset rotation for new jump
    const float gravity = 1700.0f; // Pixels per second^2
    const float jumpVelocity = -600.0f; // Initial jump velocity
    const float maxRotation = 180.0f; // Duration of rotation in seconds
};

