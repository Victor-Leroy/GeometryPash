#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <SFML/Graphics.hpp>


class BlockObject{
    std::string object_png_;
    int x_pos_;
    int y_pos_; 
    int x_repetition_;
    int y_repetition_;
    float rotation_;

public:
    BlockObject(std::string object_png, int x_pos, int y_pos, int x_repetition, int y_repetition, int rotation){
        this->object_png_ = object_png;
        this->x_pos_ = x_pos;
        this->y_pos_ = y_pos; 
        this->x_repetition_ = x_repetition;
        this->y_repetition_ = y_repetition;
        this->rotation_ = rotation*90.0f; 
    }

    std::string getObjectPNG(void){
        return this->object_png_;
    }

    int getXpos(void){
        return this->x_pos_;
    }

    int getYpos(void){
        return this->y_pos_;
    }

    int getXrepetition(void){
        return this->x_repetition_;
    }

    int getYrepetition(void){
        return this->y_repetition_;
    }

    float getRotation(void){
        return this->rotation_;
    }
};

class LevelObject {
    std::ifstream layout_file_;
    std::vector<BlockObject> list_of_blocks_;
    std::vector<sf::Sprite> list_of_block_sprites_;
    const float scrollSpeed = 150.0f;

    std::string stringToObjectPNG(std::string str){
        static const std::unordered_map<std::string, std::string> objectMap = {
            {"BLOCK", "../ressources/gfx/BLOCK.png"},
            {"SPIKE", "../ressources/gfx/SPIKE.png"},
            {"ywORB", "../ressources/gfx/ywORB.png"},
            {"ywPAD", "../ressources/gfx/ywPAD.png"},
            {"pSHIP", "../ressources/gfx/pSHIP.png"},
            {"pCUBE", "../ressources/gfx/pCUBE.png"},
            {"pUPSD", "../ressources/gfx/pUPSD.png"},
            {"pRGLR", "../ressources/gfx/pRGLR.png"}
        };

        auto it = objectMap.find(str);

        if(it != objectMap.end()){
            return it->second;
        }else{
            printf("Error: invalid block\n");
            std::exit(EXIT_FAILURE);
        }
    }


    BlockObject lineToBlock(std::string line){
        char object_type_char[20];
        int x_pos;
        int y_pos; 
        int x_repetition;
        int y_repetition;
        float rotation;

        std::sscanf(line.c_str() ,"%s %d %d %d %d %d", object_type_char, &x_pos, &y_pos,
        &x_repetition, &y_repetition, &rotation);

        std::string str(object_type_char);
        std::string object_type = stringToObjectPNG(str);
        
        BlockObject block(object_type, x_pos, y_pos, x_repetition, y_repetition, rotation*90.0f);

        return block;
    }

    void fillVector(void){
        std::string line;
        while (std::getline(layout_file_, line)) {
            BlockObject block = lineToBlock(line);
            list_of_blocks_.push_back(block);
        }
    }

    void makeListOfSprite(){
        for (BlockObject block : list_of_blocks_) {
            sf::Texture texture;
            texture.loadFromFile(block.getObjectPNG());

            sf::Vector2f position(block.getXpos(), block.getYpos());

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(position);
            sprite.setRotation(block.getRotation());
            list_of_block_sprites_.push_back(sprite);
        }
    }
    
public:
    LevelObject(std::string layout_file_name){
        this->layout_file_.open(layout_file_name);
        fillVector();
        this->layout_file_.close();

        makeListOfSprite();
    }

    std::vector<BlockObject>& getListOfBlocksReference(){
        return list_of_blocks_;
    }

    std::vector<sf::Sprite>& getListOfSpritesReference(){
        return list_of_block_sprites_;
    }

    void update(float deltaTime){
        for (sf::Sprite sprite : list_of_block_sprites_){
            sprite.move(-scrollSpeed * deltaTime, 0);
        }
    }
};
