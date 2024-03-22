#include <SFML/Graphics.hpp>
#include <cmath> // For std::abs and std::fmod
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For Time()
#include <algorithm> // For std::remove_if
#include <SFML/Audio.hpp>
#include <iostream>




class ScrollingBackground {
public:
    sf::Texture texture;
    sf::Sprite sprite1, sprite2;
    const float scrollSpeed = 100.0f; // Adjust scrolling speed

    ScrollingBackground() {
        // Load the texture
        if (!texture.loadFromFile("./sprites/gdbackground.png")) {
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



class Player {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float verticalVelocity = 0.0f;
    bool isJumping = false;
    bool isRotating = false; // Indicates if the character is currently rotating
    float rotationSpeed = 300.0f; // Speed of rotation in degrees per second
    float totalRotation = 0.0f; // Reset rotation for new jump


    Player() {
         // Load the texture
        if (!texture.loadFromFile("./sprites/icon.png")) { // Replace "character.png" with your image file
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
        const float gravity = 1700.0f; // Pixels per second^2
        const float jumpVelocity = -600.0f; // Initial jump velocity
        const float maxRotation = 180.0f; // Duration of rotation in seconds

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
};


class Game {
public:
    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture groundBackgroundTexture;
    sf::Sprite groundBackgroundSprite;
    sf::Music music; // Add a music member variable

    Game() : window(sf::VideoMode(800, 600), "Game"), ground(sf::Vector2f(800.0f, 5.0f)) {
        srand(static_cast<unsigned int>(time(0))); // Seed for random
        ground.setPosition(0, 530);

        // Load the ground background texture
        if (!groundBackgroundTexture.loadFromFile("./sprites/gdbackground.png")) {
            // handle error
        }

        // Set the ground background texture to the sprite
        groundBackgroundSprite.setTexture(groundBackgroundTexture);
        groundBackgroundSprite.setPosition(0, 530); // Position it below the ground line

        if (!music.openFromFile("./song/StereoMadness.ogg")) { // Replace with your music file path
            std::cout << "Error loading music" << std::endl;
            // Handle error (e.g., exit the game or continue without music)
        } else {
            music.setLoop(true); // Optional: Loop the music
            music.play(); // Start playing the music
        }
    }


    void run() {
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

            window.draw(groundBackgroundSprite);

            window.draw(groundSprite);
            window.draw(ground);
            
            window.display();
        }         
    }
};

