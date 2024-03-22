#include <string>

class LevelObject {
public:
    sf::Sprite sprite;  // Visual representation
    std::string type;   // Type of the object (BLOCK, SPIKE, etc.)
    int repeatsHorizontal;  // Number of horizontal repetitions
    int repeatsVertical;    // Number of vertical repetitions

    // Constructor
    LevelObject(const sf::Texture& texture, const std::string& objectType, 
                float xPosition, float yPosition, 
                int horizontalRepeats = 1, int verticalRepeats = 1) 
        : type(objectType), repeatsHorizontal(horizontalRepeats), repeatsVertical(verticalRepeats) {
        
        sprite.setTexture(texture);
        sprite.setPosition(xPosition, yPosition);
    }

    // Function to draw the object on the screen
    void draw(sf::RenderWindow& window) const {
        for (int i = 0; i < repeatsHorizontal; ++i) {
            for (int j = 0; j < repeatsVertical; ++j) {
                sf::Sprite tempSprite = sprite;  // Make a copy to manipulate
                tempSprite.move(i * sprite.getLocalBounds().width, j * sprite.getLocalBounds().height);
                window.draw(tempSprite);
            }
        }
    }
};
