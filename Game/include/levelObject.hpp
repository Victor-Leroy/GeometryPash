#pragma once

class Level {
public:
    float positionDelta = 0;
    std::vector<Obstacle> obstacles;

    void addObstacle(Obstacle obstacle) {
        obstacles.push_back(obstacle);
    }

    void draw(sf::RenderWindow& window) {
        for (auto& obstacle : obstacles) {
            window.draw(obstacle.shape);
        }
    }

      void update(float deltaTime) {
        float scrollSpeed = 230.f; // Units per second, adjust as needed
        
        for (auto& obstacle : obstacles) {
            // Move each obstacle to the left
            sf::Vector2f position = obstacle.shape.getPosition();
            position.x -= scrollSpeed * deltaTime;
            obstacle.shape.setPosition(position);
            positionDelta += scrollSpeed * deltaTime;
        }
    }  

    void loadLevelFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string typeString;
            float x, y, repeatX, repeatY;
            // int layer; 
            
            if (!(iss >> typeString >> x >> y >> repeatX >> repeatY)) {
                throw std::runtime_error("Failed to parse line: " + line);
            }
            
            ObstacleType type = stringToObstacleType(typeString);
            sf::Vector2f position(x, y);
            sf::Vector2f size(50, 50); 
            
            // Create obstacles based on repetition
            for (int i = 0; i < repeatX; i++) {
                for (int j = 0; j < repeatY; j++) {
                    sf::Vector2f pos = position + sf::Vector2f(i * size.x, j * size.y);
                    obstacles.emplace_back(type, pos, size);
                }
            }
        }
    }
   
};
