std::vector<sf::Texture> obstacleTexture;

void loadTexture() {
    sf::Texture texture;
    if (!texture.loadFromFile("../ressources/gfx/BLOCK.png")) {
        throw std::runtime_error("Unable to load obstacle texture");
    }
    obstacleTexture.push_back(texture);
    if (!texture.loadFromFile("../ressources/gfx/SPIKE.png")) {
        throw std::runtime_error("Unable to load obstacle texture");
    }
    obstacleTexture.push_back(texture);
}



enum class ObstacleType {
    SPIKE, BLOCK, ywPAD, ywORB, pUPSD, pSHIP, pRGLR, pCUBE
};

struct Obstacle {
    ObstacleType type;
    sf::Sprite shape; // Sprite for the obstacle
    
    Obstacle(ObstacleType type, const sf::Vector2f& position, const sf::Vector2f& size) {
        switch (type)
        {
        case ObstacleType::SPIKE:
            shape.setTexture(obstacleTexture[1]);
            break;
        
        case ObstacleType::BLOCK:
            shape.setTexture(obstacleTexture[0]);
            break;
        default:
            break;
        }
        shape.setPosition(position);
        shape.setScale(size.x / shape.getTexture()->getSize().x, size.y / shape.getTexture()->getSize().y);
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


