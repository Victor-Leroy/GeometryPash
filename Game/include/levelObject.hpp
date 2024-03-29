#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "levelObjectTest.hpp"

class LevelObject {
    std::string layout_file_name_ = "../ressources/level/1.txt";
    std::ifstream layout_file_;


public:
    LevelObject(string layout_file_name){
        this->layout_file_name_ = layout_file_name;
        this->layout_file_ = layout_file(layout_file_name_);
    }

    
    struct ObjectStruct{
        ObjectType object_type;
        
    }
};

