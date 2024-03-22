#ifndef COLLISION
#define COLLISION

#include <SFML/Graphics.hpp>
#include <cmath> // For std::abs and std::fmod
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For Time()
#include <algorithm> // For std::remove_if
#include<vector>

using namespace std;

class Obstacle{
public:
    sf::Sprite sprite;
    sf::Texture texture;
    float verticalVelocity = 0.0f;
    bool isJumping = false;
    bool isRotating = false; // Indicates if the character is currently rotating
    float rotationSpeed = 300.0f; // Speed of rotation in degrees per second
    float totalRotation = 0.0f; // Reset rotation for new jump

    Obstacle() {
         // Load the texture
        if (!texture.loadFromFile("../ressources/gfx/BLOCK.png")) { // Replace "character.png" with your image file
            // Handle error
        }

        // Set the texture to the sprite
        sprite.setTexture(texture);

        // Optionally, resize the sprite
        sprite.setScale(sf::Vector2f(0.5f, 0.5f)); // Example scale

        // Set the starting position of the sprite
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f); // Set the origin to the center of the texture
        sprite.setPosition(600.0f, 500.0f); // Starting position
    }

    void update(float deltaTime) {
        // Update position
        sprite.move(-100.0f * deltaTime, 0);

        // Example ground check
        if (sprite.getPosition().y >= 500.0f) {
            sprite.setPosition(sprite.getPosition().x, 500.0f);
            verticalVelocity = 0.0f;
        }
    }
};

#endif