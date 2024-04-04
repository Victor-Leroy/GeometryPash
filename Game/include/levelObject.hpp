class Level {
public:
    std::vector<Obstacle> obstacles;

    void addObstacle(const sf::Vector2f& position, const sf::Vector2f& size) {
        obstacles.emplace_back(position, size);
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
