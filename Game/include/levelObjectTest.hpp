#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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

class GameObject {
private:
    ObjectType m_type;
    float m_rotation;
    sf::Vector2f m_pos;
    sf::FloatRect m_hitbox;
    sf::Texture m_object_texture;
    sf::Sprite m_sprite;  // SFML uses Sprites to render textures

public:
    GameObject(ObjectType type, float rotation, sf::Vector2f pos, sf::FloatRect hitbox, const std::string& texturePath)
        : m_type(type), m_rotation(rotation), m_pos(pos), m_hitbox(hitbox) {
        
        if (!m_object_texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        
        m_sprite.setTexture(m_object_texture);
        m_sprite.setPosition(m_pos);
        m_sprite.setRotation(m_rotation);
        // Adjust the sprite's origin if necessary, e.g., to rotate around its center
        // m_sprite.setOrigin(m_object_texture.getSize().x / 2.0f, m_object_texture.getSize().y / 2.0f);
    }

    const sf::FloatRect& get_hitbox() const {
        // You may need to adjust this based on your hitbox requirements
        return m_sprite.getGlobalBounds();
    }

    sf::Vector2f get_pos() const {
        return m_pos;
    }

    ObjectType get_type() const {
        return m_type;
    }

    void render(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }
};
