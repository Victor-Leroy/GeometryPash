enum levelType{
    BLOCK,
    SPIKE,
    ywORB,
    ywPAD,
    pSHIP,
    pCUBE,
    pUPSD,
    pRGLR
};

class LevelObject {
public:
    sf::Sprite sprite;
    std::string name;
    float xPos, yPos;
    int repeatsHorizontal, repeatsVertical;

    // Pseudo-code to load a texture based on the object name
    sf::Texture& getTextureForName(const std::string& name) {
        static std::map<std::string, sf::Texture> textures;
        // Lazy load textures
        if (textures.empty()) {
            textures["BLOCK"].loadFromFile("./sprites/block.png");
            textures["SPIKE"].loadFromFile("./sprites/spike.png");
            textures["ywORB"].loadFromFile("./sprites/ywORB.png");            
            textures["ywPAD"].loadFromFile("./sprites/ywPAD.png");
            textures["pSHIP"].loadFromFile("./sprites/pSHIP.png");
            textures["pCUBE"].loadFromFile("./sprites/pCUBE.png");
            textures["pUPSD"].loadFromFile("./sprites/pUPSD.png");
            textures["pRGLR"].loadFromFile("./sprites/pRGLR.png");        
        }
        return textures[name];
    }

    LevelObject createLevelObjectFromData(const std::string& objectName, float xPosition, float yPosition, int hRepeats, int vRepeats) {
        sf::Texture& texture = getTextureForName(objectName);
        return LevelObject(texture, objectName, xPosition, yPosition, hRepeats, vRepeats);
    }

};



std::vector<LevelObject> loadLevelData(const std::string& filePath) {
    std::ifstream file(filePath);
    std::vector<LevelObject> levelObjects;

    if (!file) {
        std::cerr << "Unable to open level data file: " << filePath << std::endl;
        return levelObjects;
    }

    int numberOfLines;
    file >> numberOfLines;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string objectName;
    float xPos, yPos;
    int repeatsHorizontal, repeatsVertical;

    for (int i = 0; i < numberOfLines; ++i) {
        std::string line;
        std::getline(file, line);
        std::istringstream lineStream(line);
        if (lineStream >> objectName >> xPos >> yPos >> repeatsHorizontal >> repeatsVertical) {
            levelObjects.push_back({objectName, xPos, yPos, repeatsHorizontal, repeatsVertical});
        }
    }

    return levelObjects;
};