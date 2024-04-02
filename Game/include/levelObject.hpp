#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <cstdlib>


class BlockObject{
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

private:
    ObjectType object_type_;
    int x_pos_;
    int y_pos_; 
    int x_repetition_;
    int y_repetition_;
    int rotation_; 

public:
    BlockObject(ObjectType object_type, int x_pos, int y_pos, int x_repetition, int y_repetition, int rotation){
        this->object_type_ = object_type;
        this->x_pos_ = x_pos;
        this->y_pos_ = y_pos; 
        this->x_repetition_ = x_repetition;
        this->y_repetition_ = y_repetition;
        this->rotation_ = rotation; 
    }

    ObjectType getObjectType(void){
        return this->object_type_;
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

    int getRotation(void){
        return this->rotation_;
    }
};

class LevelObject {
    std::ifstream layout_file_;
    std::vector<BlockObject> list_of_blocks_;

    BlockObject::ObjectType stringToObjectType(std::string str){
        static const std::unordered_map<std::string, BlockObject::ObjectType> objectMap = {
            {"BLOCK", BlockObject::ObjectType::BLOCK},
            {"HAZARD", BlockObject::ObjectType::HAZARD},
            {"ORB", BlockObject::ObjectType::ORB},
            {"PAD", BlockObject::ObjectType::PAD},
            {"SHIP_PORTAL", BlockObject::ObjectType::SHIP_PORTAL},
            {"CUBE_PORTAL", BlockObject::ObjectType::CUBE_PORTAL},
            {"UPSIDE_DOWN_PORTAL", BlockObject::ObjectType::UPSIDE_DOWN_PORTAL},
            {"NORMAL_PORTAL", BlockObject::ObjectType::NORMAL_PORTAL}
        };

        auto it = objectMap.find(str);
        if(it != objectMap.end()){
            return it->second;
        }else{
            printf("Error: invalid block");
            std::exit(EXIT_FAILURE);
        }
    }


    BlockObject lineToBlock(std::string line){
        char object_type_char[20];
        int x_pos;
        int y_pos; 
        int x_repetition;
        int y_repetition;
        int rotation; 

        std::sscanf("%s %d %d %d %d %d", object_type_char, &x_pos, &y_pos,
        &x_repetition, &y_repetition, &rotation);

        std::string str(object_type_char);
        BlockObject::ObjectType object_type = stringToObjectType(str);
        
        BlockObject block(object_type, x_pos, y_pos, x_repetition, y_repetition, rotation);

        return block;
    }

    void fillVector(void){
        std::string line;
        while (getline(layout_file_, line)) {
            BlockObject block = lineToBlock(line);
            list_of_blocks_.push_back(block);
        }
    }
    
public:
    LevelObject(std::string layout_file_name){
        this->layout_file_.open(layout_file_name);
        fillVector();
        this->layout_file_.close();
    }

    std::vector<BlockObject>& getListOfBlocksReference(){
        return list_of_blocks_;
    }
};
