struct Obstacle {
    sf::RectangleShape shape;
    // Add more properties if needed, like type, behavior, etc.
    
    Obstacle(const sf::Vector2f& position, const sf::Vector2f& size) {
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(sf::Color::Red); // Just an example, color it as you like
    }
};
