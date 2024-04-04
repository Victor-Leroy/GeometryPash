class Level {
public:
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
        float scrollSpeed = 200.f; // Units per second, adjust as needed
        
        for (auto& obstacle : obstacles) {
            // Move each obstacle to the left
            sf::Vector2f position = obstacle.shape.getPosition();
            position.x -= scrollSpeed * deltaTime;
            obstacle.shape.setPosition(position);
        }
      }  
   
};
