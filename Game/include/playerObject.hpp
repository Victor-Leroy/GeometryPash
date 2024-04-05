
class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float ground = 500.0f;

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
        sprite.setPosition(300.0f, ground); // Starting position
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
            ground = 500.0f;
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
        if (sprite.getPosition().y >= ground) {
            sprite.setPosition(sprite.getPosition().x, ground);
            verticalVelocity = 0.0f;
        }
    }

    bool isOnGround() {
        return sprite.getPosition().y >= ground; // Simplified ground check
    }

    void jump() {
        if (isOnGround()) {
            isJumping = true;
        }
    }

    enum struct CollisionDirection {
        None,
        Left,
        Right,
        Top,
        Bottom
    };


    void findCollision(Level *level){

        bool resetGround = true;

        for (auto& obstacle : level->obstacles){
            float dx = this->sprite.getPosition().x - obstacle.shape.getPosition().x;
            float dy = this->sprite.getPosition().y - obstacle.shape.getPosition().y;
            float distance = std::sqrt(dx * dx + dy * dy);
            if(distance < 50 && distance > -50){
                sf::FloatRect player_rect = this->sprite.getGlobalBounds();
                sf::FloatRect object_rect = obstacle.shape.getGlobalBounds();

                sf::FloatRect intersection;
                if(object_rect.intersects(player_rect, intersection)){

                    float combinedHalfWidths = (player_rect.width + object_rect.width) / 2;
                    float combinedHalfHeights = (player_rect.height + object_rect.height) / 2;

                    float offsetX = fabs(dx);
                    float offsetY = fabs(dy);

                    float penetrationX = combinedHalfWidths - offsetX;
                    float penetrationY = combinedHalfHeights - offsetY;

                    if (penetrationX > penetrationY) {
                        if (dy > 0) {
                            // CollisionDirection::Top; // Collision from top
                            std::cout << "Top" << std::endl;
                        } else {
                            //return CollisionDirection::Bottom; // Collision from bottom
                            std::cout << "Bottom" << std::endl;
                        }
                    } else {
                        if (dx > 0) {
                            //return CollisionDirection::Left; // Collision from left
                            std::cout << "Left" << std::endl;
                        } else {
                            //return CollisionDirection::Right; // Collision from right
                            std::cout << "Left" << std::endl;
                        }
                    }


                    this->ground = object_rect.top - 25;
                    this->sprite.setRotation(0);
                    resetGround = false;
                    //std::cout << player_rect.top << std::endl;
                    /*if((player_rect.top - player_rect.height) < object_rect.top){
                        std::cout << object_rect.height << std::endl;
                        this->ground = object_rect.top;
                    }*/
                    //std::cout << "kill" << std::endl;
                }
            }
        }

        if(resetGround){
            this->ground = 500;
            resetGround = true;
        }
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

