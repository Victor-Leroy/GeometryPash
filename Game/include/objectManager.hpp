#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"  // Make sure this is the adapted SFML version

class ObjectManager {
private:
    std::vector<GameObject> m_objects;
    std::map<std::string, ObjectType> m_string_to_type;  // Using the ObjectType enum
    std::map<ObjectType, sf::FloatRect> m_type_to_hitbox;  // SFML rect type

public:
    ObjectManager() {
        // Initialize m_string_to_type based on your game's object types
        // Example:
        m_string_to_type["BLOCK"] = ObjectType::BLOCK;
        m_string_to_type["HAZARD"] = ObjectType::HAZARD;
        m_string_to_type["ORB"] = ObjectType::ORB;
        m_string_to_type["PAD"] = ObjectType::PAD;
        m_string_to_type["SHIP_PORTAL"] = ObjectType::SHIP_PORTAL;
        m_string_to_type["CUBE_PORTAL"] = ObjectType::CUBE_PORTAL;
        m_string_to_type["UPSIDE_DOWN_PORTAL"] = ObjectType::UPSIDE_DOWN_PORTAL;   
        m_string_to_type["NORMAL_PORTAL"] = ObjectType::NORMAL_PORTAL;
   
        // Initialize hitboxes for each type if necessary
        // Example:
        m_type_to_hitbox[ObjectType::BLOCK] = sf::FloatRect(0.f, 0.f, 50.f, 50.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::HAZARD] = sf::FloatRect(0.f, 0.f, 30.f, 30.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::ORB] = sf::FloatRect(0.f, 0.f, 20.f, 20.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::PAD] = sf::FloatRect(0.f, 0.f, 40.f, 40.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::SHIP_PORTAL] = sf::FloatRect(0.f, 0.f, 60.f, 60.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::CUBE_PORTAL] = sf::FloatRect(0.f, 0.f, 60.f, 60.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::UPSIDE_DOWN_PORTAL] = sf::FloatRect(0.f, 0.f, 60.f, 60.f);  // Placeholder values
        m_type_to_hitbox[ObjectType::NORMAL_PORTAL] = sf::FloatRect(0.f, 0.f, 60.f, 60.f);  // Placeholder values
        // Add more as necessary
    }

    const std::vector<GameObject>& get_objects() const {
        return m_objects;
    }

    // Assuming a simple rotation system that works in 90-degree increments
    sf::FloatRect rotate_hitbox(const sf::FloatRect& hitbox, int rotations) {
        // Rotations might be more complex in SFML, potentially requiring a different approach
        // This is a placeholder to indicate the method needs adaptation for meaningful use
        return hitbox;  // Simple pass-through for now
    }

    void clear_objects() {
        m_objects.clear();
    }

    void load_level_data(const std::string& filePath) {
        // Implementation depends on your level data format
        // You might parse a file here and create GameObjects based on its contents
    }

    void render(sf::RenderWindow& window) {
        for (const auto& object : m_objects) {
            object.render(window);
        }
    }
};
