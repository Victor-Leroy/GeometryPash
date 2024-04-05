enum class ObstacleType {
    SPIKE, BLOCK, ywPAD, ywORB, pUPSD, pSHIP, pRGLR, pCUBE
};

struct Obstacle {
    ObstacleType type;
    sf::RectangleShape shape; // For simplicity, using a rectangle shape for all types
    sf::Texture texture; // Texture for the obstacle
    
    Obstacle(ObstacleType type, const sf::Vector2f& position, const sf::Vector2f& size)
        : type(type), shape(size) {
        shape.setPosition(position);
        // You can set the color or texture based on the type
                // Load the texture based on the type
        if (type == ObstacleType::BLOCK) {
            if (!texture.loadFromFile("/Users/victor/Documents/GitHub/GD-Clone/Game/ressources/gfx/BLOCK.png")) {
                // handle error...
            }
            shape.setTexture(&texture);
        }
        else if (type == ObstacleType::SPIKE) {
            if (!texture.loadFromFile("/Users/victor/Documents/GitHub/GD-Clone/Game/ressources/gfx/SPIKE.png")) {
                // handle error...
            }
            shape.setTexture(&texture);
        }
        // Add similar code for other obstacle types if needed
    }
};

ObstacleType stringToObstacleType(const std::string& typeString) {
    if (typeString == "SPIKE") return ObstacleType::SPIKE;
    else if (typeString == "BLOCK") return ObstacleType::BLOCK;
    else if (typeString == "ywPAD") return ObstacleType::ywPAD;
    else if (typeString == "ywORB") return ObstacleType::ywORB;
    else if (typeString == "pUPSD") return ObstacleType::pUPSD;
    else if (typeString == "pSHIP") return ObstacleType::pSHIP;
    else if (typeString == "pRGLR") return ObstacleType::pRGLR;
    else if (typeString == "pCUBE") return ObstacleType::pCUBE;
    else throw std::runtime_error("Unknown obstacle type: " + typeString);
}

void loadLevelFromFile(const std::string& filename, std::vector<Obstacle>& obstacles) {
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
        sf::Vector2f size(50, 50); // Example size, adjust based on the type
        
        // Create obstacles based on repetition
        for (int i = 0; i < repeatX; i++) {
            for (int j = 0; j < repeatY; j++) {
                sf::Vector2f pos = position + sf::Vector2f(i * size.x, j * size.y);
                obstacles.emplace_back(type, pos, size);
            }
        }
    }
}

