#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "levelObjectTest.hpp"
#include <regex>

using namespace std;

class LevelObject {
    // string layout_file_name_ = "../ressources/level/1.txt";
    // ifstream layout_file_("../ressources/level/1.txt");
    ifstream layout_file_;

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

    LevelObject(/*string layout_file_name*/) : layout_file_("../ressources/level/1.txt"){
        // this->layout_file_name_ = layout_file_name;
        // this->layout_file_ = layout_file_(layout_file_name_);

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
        string line;
        cout << "Reading from the file" << endl;
        while(getline(layout_file_, line)){
            lineToObject(line);
        }
        return;
    }

    void lineToObject(string line) {
        ObjectStruct object;
        scanf("%s %d %d %d %d %d", object.object_type, object.x_pos, object.y_pos, object.x_repetition, object.y_repetition, object.rotation);
        // createObstacle(object);
        cout << object.x_pos << endl;
        return;
    }

    sf::Sprite obstacle;
    sf::Texture obstacleTexture;
    float Test_x = 500.0f;
    float Test_y = 300.0f;

    void createObstacle(sf::RenderWindow& window) {
        ObjectStruct object;
        object.object_type = ObjectType::BLOCK;
        object.rotation = 0;
        object.x_pos = Test_x;
        object.y_pos = Test_y;
        object.x_repetition = 3;
        object.y_repetition = 1;
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

        obstacle.setScale(sf::Vector2f(0.5f, 0.5f));

        for(object.y_repetition; object.y_repetition > 0; object.y_repetition--){
                for(object.x_repetition; object.x_repetition > 0; object.x_repetition--){
                    obstacle.setPosition(object.x_pos, object.y_pos);
                    obstacle.setRotation(object.rotation);
                    object.x_pos += 50;
                    window.draw(obstacle);
            }
            object.y_pos += 50;
        }
        return;     

    }

    void update(float deltaTime){
        Test_x -= 100.0f * deltaTime;
    }

};
