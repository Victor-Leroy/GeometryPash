#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "levelObjectTest.hpp"
#include <regex>


class LevelObject {
    std::string layout_file_name_ = "../ressources/level/1.txt";
    std::ifstream layout_file_;


public:

    enum class ObjectType {
        BLOCK,
        HAZARD,
        ORB,
        PAD,
        SHIP_PORTAL,
        CUBE_PORTAL,
        UPSIDE_DOWN_PORTAL,
        NORMAL_PORTAL
    };

    LevelObject(std::string layout_file_name){
        this->layout_file_name_ = layout_file_name;
        this->layout_file_ = layout_file_(layout_file_name_);
    }

    
    struct ObjectStruct {
        ObjectType object_type;
        int x_pos;
        int y_pos; 
        int x_repetition;
        int y_repetition;
        int rotation; 
               
    }; 

    void getFileInformation() {
        std::string line;
        std::cout << "Reading from the file" << std::endl;
        while(getline(layout_file_, line)){
            lineToObject(line);
        }
        return;
    }

    void lineToObject(std::string line) {
        ObjectStruct object;
        std::scanf("%s %d %d %d %d %d", object.object_type, object.x_pos, object.y_pos, object.x_repetition, object.y_repetition, object.rotation);
        createObstacle(object);
        return;
    }

    void createObstacle(ObjectStruct object) {
        sf::Sprite obstacle;
        sf::Texture obstacleTexture;
        switch(object.object_type){
        case ObjectType::BLOCK:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/BLOCK.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::HAZARD:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/SPIKE.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::ORB:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/ywORB.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::PAD:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/ywPAD.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::SHIP_PORTAL:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/pSHIP.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::CUBE_PORTAL:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/pCUBE.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::UPSIDE_DOWN_PORTAL:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/pUPSD.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        case ObjectType::NORMAL_PORTAL:
            if (!obstacleTexture.loadFromFile("../ressources/gfx/pRGLR.png")) { // Replace "character.png" with your image file
            // Handle error
            }   
            obstacle.setTexture(obstacleTexture);
            break;
        default:
            break; 
        }

        for(object.y_repetition; object.y_repetition > 0; object.y_repetition--){
                for(object.x_repetition; object.x_repetition > 0; object.x_repetition--){
                    obstacle.setPosition(object.x_pos, object.y_pos);
                    obstacle.setRotation(object.rotation);
                    object.x_pos += 50;
            }
            object.y_pos += 50;
        }
        return;     

    }

};
